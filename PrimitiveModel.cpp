//Mesh Rednerer
//DXGameObject의 컴포넌트로 사용
//새로 만드는 DXMeshRenderer는 반드시 Component 폴더에 파일 생성
#include "PrimitiveModel.h"

void PrimitiveCube::MakePrimitive(const std::string& texFilename)
{
	std::vector<Texture> textures;

	if (!texFilename.empty())
		textures.push_back(Texture(device, texFilename));
	else
		textures.push_back(Texture(device, Colors::UnloadedTextureColor));

	std::vector<ModelVertex> vertices =
	{
		ModelVertex(-0.5, 0.5f, 0.5f,   0.0f, 0.0f,   -0.5f, 0.5f, 0.5f),		// 0 top far left
		ModelVertex(0.5, 0.5f, 0.5f,   1.0f, 0.0f,   0.5f, 0.5f, 0.5f),			// 1 top far right
		ModelVertex(0.5, 0.5f, -0.5f,   1.0f, 1.0f,   0.5f, 0.5f, -0.5f),		// 2 top near right
		ModelVertex(-0.5, 0.5f, -0.5f,   0.0f, 1.0f,   -0.5f, 0.5f, -0.5f),		// 3 top near left

		ModelVertex(-0.5, -0.5f, 0.5f,   0.0f, 1.0f,   -0.5f, -0.5f, 0.5f),		// 4 bottom far left
		ModelVertex(0.5, -0.5f, 0.5f,   1.0f, 1.0f,   0.5f, -0.5f, 0.5f),		// 5 bottom far right
		ModelVertex(0.5, -0.5f, -0.5f,   1.0f, 0.0f,   0.5f, -0.5f, -0.5f),		// 6 bottom near right
		ModelVertex(-0.5, -0.5f, -0.5f,   0.0f, 0.0f,   -0.5f, -0.5f, -0.5f),	// 7 bottom near left

		ModelVertex(0.5, -0.5f, 0.5f,   0.0f, 0.0f,   0.5f, -0.5f, 0.5f),		// 8 other bottom far right
		ModelVertex(0.5, -0.5f, -0.5f,   0.0f, 1.0f,   0.5f, -0.5f, -0.5f),		// 9 other bottom near right
		ModelVertex(-0.5, -0.5f, -0.5f,   1.0f, 1.0f,   -0.5f, -0.5f, -0.5f),	// 10 other bottom near left
		ModelVertex(-0.5, -0.5f, 0.5f,   1.0f, 0.0f,   -0.5f, -0.5f, 0.5f),		// 11 other bottom far left
	};

	std::vector<DWORD> indices =
	{
		0,1,2,   0,2,3,		// top
		7,6,5,   7,5,4,		// bottom
		3,2,6,   3,6,7,		// near
		2,1,8,   2,8,9,		// right
		1,0,4,   1,4,5,		// far
		0,3,10,   0,10,11,	// left	
	};

	mesh = std::make_unique<Mesh>(device, deviceContext, vertices, indices, textures, XMMatrixIdentity());
} // PrimitiveCod::MakePrimitive

void PrimitiveShpher::MakePrimitive(const std::string& texFilename)
{
	std::vector<Texture> textures;

	if (!texFilename.empty())
		textures.push_back(Texture(device, texFilename));
	else
		textures.push_back(Texture(device, Colors::UnloadedTextureColor));

	std::vector<ModelVertex> vertices;
	std::vector<DWORD> indices;

	float sectorStep = XM_2PI / SectorCount;
	float stackStep = XM_PI / StackCount;
	float sectorAngle, stackAngle;
	float x, y, z, xy;

	for (int i = 0; i <= StackCount; i++)
	{
		stackAngle = XM_PI / 2 - i * stackStep; // radian: (pi/2)에서 (-pi/2)까지
		xy = cosf(stackAngle); // radius * cos(radian)
		z = sinf(stackAngle); // radius * sin(radian)
		for (int j = 0; j <= SectorCount; ++j)
		{
			ModelVertex vertex;
			sectorAngle = j * sectorStep; // 0부터 2pi까지
			// setup position
			x = xy * cosf(sectorAngle); // radius * cos(radian) * cos(radian)
			y = xy * sinf(sectorAngle); // radius * cos(radian) * sin(radian)
			vertex.pos = { x, y, z };
			// setup normal
			XMStoreFloat3(&vertex.normal, XMVector3Normalize(XMVectorSet(x, y, z, 0.0f)));
			// setup tex coord (u, v)
			vertex.texCoord = { (float)j / SectorCount, (float)i / StackCount };
			vertices.push_back(vertex);
		}
	}

	int k1, k2;
	for (int i = 0; i < StackCount; ++i)
	{
		k1 = i * (SectorCount + 1);
		k2 = k1 + SectorCount + 1;
		for (int j = 0; j < SectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != (StackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	mesh = std::make_unique<Mesh>(device, deviceContext, vertices, indices, textures, XMMatrixIdentity());
} // PrimitiveSphere::MakePrimitive