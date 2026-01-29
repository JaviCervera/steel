#pragma once

#include "../interface/model_manager.h"
#include "platform_irrlicht.h"

struct DataReader
{
	DataReader(const void *data)
			: m_data(reinterpret_cast<const unsigned char *>(data)),
				m_offset(0) {}

	void read(void *buffer, size_t size)
	{
		memcpy(buffer, m_data + m_offset, size);
		m_offset += size;
	}

	unsigned char readByte()
	{
		return m_data[m_offset++];
	}

	unsigned short readShort()
	{
		unsigned short value = *reinterpret_cast<const unsigned short *>(m_data + m_offset);
		m_offset += sizeof(unsigned short);
		return value;
	}

	int readInt()
	{
		int value = *reinterpret_cast<const int *>(m_data + m_offset);
		m_offset += sizeof(int);
		return value;
	}

	float readFloat()
	{
		float value = *reinterpret_cast<const float *>(m_data + m_offset);
		m_offset += sizeof(float);
		return value;
	}

private:
	const unsigned char *m_data;
	size_t m_offset;
};

struct ModelManagerIrrlicht : public ModelManager
{
	ModelManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	Model *createModel(const void *data)
	{
		irr::scene::SMesh *mesh = new irr::scene::SMesh();
		DataReader vertex_reader(data);
		const unsigned short buffer_count = vertex_reader.readShort();
		for (unsigned short b = 0; b < buffer_count; ++b)
		{
			union
			{
				irr::scene::IMeshBuffer *base;
				irr::scene::SMeshBuffer *standard;
				irr::scene::SMeshBufferLightMap *lightmap;
			} mesh_buffer;
			const unsigned char has_2uvs = vertex_reader.readByte();
			const unsigned short vertex_count = vertex_reader.readShort();
			const unsigned short index_count = vertex_reader.readShort();
			if (has_2uvs)
			{
				mesh_buffer.lightmap = new irr::scene::SMeshBufferLightMap();
				mesh_buffer.lightmap->Vertices.set_used(vertex_count);
				mesh_buffer.lightmap->Indices.set_used(index_count);
			}
			else
			{
				mesh_buffer.standard = new irr::scene::SMeshBuffer();
				mesh_buffer.standard->Vertices.set_used(vertex_count);
				mesh_buffer.standard->Indices.set_used(index_count);
			}
			for (unsigned short v = 0; v < vertex_count; ++v)
			{
				const float x = vertex_reader.readFloat();
				const float y = vertex_reader.readFloat();
				const float z = vertex_reader.readFloat();
				const float nx = vertex_reader.readFloat();
				const float ny = vertex_reader.readFloat();
				const float nz = vertex_reader.readFloat();
				const int color = vertex_reader.readInt();
				const float u1 = vertex_reader.readFloat();
				const float v1 = vertex_reader.readFloat();
				float u2 = has_2uvs ? vertex_reader.readFloat() : 0.0f;
				float v2 = has_2uvs ? vertex_reader.readFloat() : 0.0f;
				if (has_2uvs)
					mesh_buffer.lightmap->Vertices[v] = irr::video::S3DVertex2TCoords(
							irr::core::vector3df(x, y, z),
							irr::core::vector3df(nx, ny, nz),
							irr::video::SColor(color),
							irr::core::vector2d<irr::f32>(u1, v1),
							irr::core::vector2d<irr::f32>(u2, v2));
				else
					mesh_buffer.standard->Vertices[v] = irr::video::S3DVertex(
							irr::core::vector3df(x, y, z),
							irr::core::vector3df(nx, ny, nz),
							irr::video::SColor(color),
							irr::core::vector2d<irr::f32>(u1, v1));
			}
			for (unsigned short i = 0; i < index_count; ++i)
			{
				if (has_2uvs)
					mesh_buffer.lightmap->Indices[i] = vertex_reader.readShort();
				else
					mesh_buffer.standard->Indices[i] = vertex_reader.readShort();
			}
			mesh->addMeshBuffer(mesh_buffer.base);
			mesh_buffer.base->drop();
		}
		mesh->recalculateBoundingBox();
		irr::scene::IMeshSceneNode *node = m_platform->device().getSceneManager()->addMeshSceneNode(mesh);
		mesh->drop();
		return reinterpret_cast<Model *>(node);
	}

	Model *createCubeModel()
	{
		return reinterpret_cast<Model *>(scene().addCubeSceneNode(1));
	}

	Model *createSphereModel()
	{
		return reinterpret_cast<Model *>(scene().addSphereSceneNode(0.5f));
	}

private:
	PlatformIrrlicht *m_platform;

	irr::scene::ISceneManager &scene()
	{
		return *m_platform->device().getSceneManager();
	}
};
