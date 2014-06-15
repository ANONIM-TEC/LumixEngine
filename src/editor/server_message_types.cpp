#include "core/lux.h"
#include "server_message_types.h"
#include "core/blob.h"


namespace Lux
{

	/*
void EntityPositionMessage::write(IStream& stream)
{
	stream.write(&index, sizeof(index));
	stream.write(&x, sizeof(x));
	stream.write(&y, sizeof(y));
	stream.write(&z, sizeof(z));
}
*/

void EntityPositionEvent::read(Blob& stream)
{
	stream.read(&index, sizeof(index));
	stream.read(&x, sizeof(x));
	stream.read(&y, sizeof(y));
	stream.read(&z, sizeof(z));
}

/*
void EntitySelectedMessage::write(IStream& stream) 
{
	stream.write(&index, sizeof(index));
	int32_t count = components.size();
	stream.write(&count, sizeof(count));
	for(int i = 0; i < count; ++i)
	{
		stream.write(&components[i], sizeof(components[i]));
	}
}
*/

void EntitySelectedEvent::read(Blob& stream)
{
	stream.read(&index, sizeof(index));
	int32_t count;
	stream.read(&count, sizeof(count));
	components.resize(count);
	for(int i = 0; i < count; ++i)
	{
		stream.read(&components[i], sizeof(components[i]));
	}
}


void LogEvent::read(Blob& stream)
{
	stream.read(&type, sizeof(type));
	int32_t len;
	stream.read(&len, sizeof(len));
	char tmp[255];
	if(len < 255)
	{
		stream.read(tmp, len);	
		tmp[len] = 0;
	}
	system = tmp;
	stream.read(&len, sizeof(len));
	if(len < 255)
	{
		stream.read(tmp, len);	
		tmp[len] = 0;
		message = tmp;
	}
	else
	{
		char* buf = LUX_NEW_ARRAY(char, len+1);
		stream.read(buf, len);
		buf[len] = 0;
		message = buf;
		LUX_DELETE_ARRAY(buf);
	}
}


/*
void PropertyListMessage::write(IStream& stream)
{
	int32_t count = properties.size();
	stream.write(&count, sizeof(count));
	stream.write(&type_hash, sizeof(type_hash));
	for(int i = 0; i < count; ++i)
	{
		stream.write(&properties[i].name_hash, sizeof(properties[i].name_hash));
		stream.write(&properties[i].data_size, sizeof(properties[i].data_size));
		stream.write(properties[i].data, properties[i].data_size);
	}
}
*/

void PropertyListEvent::read(Blob& stream)
{
	int32_t count;
	stream.read(&count, sizeof(count));
	properties.resize(count);
	stream.read(&type_hash, sizeof(type_hash));
	for(int i = 0; i < count; ++i)
	{
		stream.read(&properties[i].name_hash, sizeof(properties[i].name_hash));
		stream.read(&properties[i].data_size, sizeof(properties[i].data_size));
		properties[i].data = LUX_NEW_ARRAY(uint8_t, properties[i].data_size);
		stream.read(properties[i].data, properties[i].data_size);
	}
}


} // ~namespace Lux
