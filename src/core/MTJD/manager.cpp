#include "core/lux.h"
#include "core/MTJD/manager.h"

#include "core/MTJD/job.h"
#include "core/MTJD/scheduler.h"
#include "core/MTJD/worker_thread.h"

#include "core/MT/thread.h"

namespace Lux
{
	namespace MTJD
	{
		Manager::Manager()
			: m_scheduling_counter(0)
			, m_scheduler(*this)
		{
#if TYPE == MULTI_THREAD
			uint32_t threads_num = getCpuThreadsCount();

			m_scheduler.create("Scheduler");
			m_scheduler.run();

			m_worker_tasks = LUX_NEW_ARRAY(WorkerTask, threads_num);
			for (uint32_t i = 0; i < threads_num; ++i)
			{
				m_worker_tasks[i].create("MTJD::WorkerTask", this, &m_trans_queue);
				m_worker_tasks[i].setAffinityMask(getAffinityMask(i));
				m_worker_tasks[i].run();
			}

#endif //TYPE == MULTI_THREAD
		}

		Manager::~Manager()
		{
#if TYPE == MULTI_THREAD

			uint32_t threads_num = getCpuThreadsCount();
			for (uint32_t i = 0; i < threads_num; ++i)
			{
				m_trans_queue.abort();
			}

			for (uint32_t i = 0; i < threads_num; ++i)
			{
				m_worker_tasks[i].destroy();
			}

			m_scheduler.forceExit(false);
			m_scheduler.dataSignal();
			m_scheduler.destroy();

			LUX_DELETE_ARRAY(m_worker_tasks);

#endif //TYPE == MULTI_THREAD
		}

		uint32_t Manager::getCpuThreadsCount() const
		{
#if TYPE == MULTI_THREAD
			
			return MT::getCPUsCount();

#else //TYPE == MULTI_THREAD

			return 1;

#endif //TYPE == MULTI_THREAD
		}


		void Manager::schedule(Job* job)
		{
			ASSERT(NULL != job);
			ASSERT(false == job->m_scheduled);
			ASSERT(job->m_dependency_count > 0);

#if TYPE == MULTI_THREAD

			if (1 == job->getDependenceCount())
			{
				pushReadyJob(job);

				job->m_scheduled = true;
				m_scheduler.dataSignal();
			}

#else //TYPE == MULTI_THREAD

			job->execute();
			job->onExecuted();

#endif //TYPE == MULTI_THREAD
		}

		void Manager::scheduleCpu(Job* job)
		{
			JobTrans* tr = m_trans_queue.alloc(false);
			if (tr)
			{
				tr->data = job;
				if (!m_trans_queue.push(tr, false))
				{
					m_trans_queue.dealoc(tr, true);
					pushReadyJob(job);
				}
				else
				{
					m_pending_trans.push(tr);
				}
			}
		}

		void Manager::doScheduling()
		{
#if TYPE == MULTI_THREAD

			uint32_t count = MT::atomicIncrement(&m_scheduling_counter);
			if (1 == count)
			{
				do
				{
					for (int i = 0; i < m_pending_trans.size();)
					{
						JobTrans* tr = m_pending_trans[i];
						if (tr->isCompleted())
						{
							tr->data->onExecuted();
							m_trans_queue.dealoc(tr, true);
							m_pending_trans.eraseFast(i);
						}
						else
						{
							++i;
						}
					}

					Job* job = getNextReadyJob();
					if (NULL != job)
					{
						scheduleCpu(job);
					}

					count = MT::atomicDecrement(&m_scheduling_counter);
				} while (0 < count);
			}

#endif //TYPE == MULTI_THREAD
		}

		Job* Manager::getNextReadyJob()
		{
#if TYPE == MULTI_THREAD

			for (int32_t i = 0; i < (int32_t)Priority::Count; ++i)
			{
				if (!m_ready_to_execute[i].isEmpty())
				{
					Job** entry = m_ready_to_execute[i].pop(true);
					Job* ret = *entry;
					m_ready_to_execute[i].dealoc(entry, true);

					return ret;
				}
			}

#endif //TYPE == MULTI_THREAD

			return NULL;
		}

		void Manager::pushReadyJob(Job* job)
		{
			ASSERT(NULL != job);

#if TYPE == MULTI_THREAD

			Job** jobEntry = m_ready_to_execute[(int32_t)job->getPriority()].alloc(true);
			if (jobEntry)
			{
				*jobEntry = job;
				m_ready_to_execute[(int32_t)job->getPriority()].push(jobEntry, true);
			}

			//int32_t idx = -1;
			//while (-1 == idx)
			//	idx = m_ready_to_execute[(int32_t)job->getPriority()].push(job);

#endif //TYPE == MULTI_THREAD
		}

		uint32_t Manager::getAffinityMask(uint32_t idx) const
		{
#if defined(_WIN32) || defined(_WIN64)
			idx = 0;
			return MT::getProccessAffinityMask();
#elif defined(OSX)
			return MT::getProccessAffinityMask();
#else
#error "Not Supported!"
#endif
		}
	} // ~namepsace MTJD
} // ~namepsace Lux