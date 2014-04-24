#ifndef TEXTUREHELPER_H_
#define TEXTUREHELPER_H_

#include <string>

class TextureHelper
{
private:

	std::string defaulPatch;
	std::string defaultFolder;
	std::string texturePatch;
	std::string fileName;

public:

	enum Textures
	{
		Genesis,
		PspTeam,
		Logo,
		Utils,
		Dirt,
		Glass,
		Terrain,
		Blue,
		Sky,
		Sun,
		Moon,
		lameCraft,
		Red,
		NetherSky,
		screen1,
		screen2,
		screen3,
		screen4,
		clouds1,
		inv,
	};

	static TextureHelper m_TextureHelper;
	static TextureHelper* Instance();


	TextureHelper();
	~TextureHelper();

	int GetTexture(Textures texture);

	void SetTextureFolderName(std::string name);
};

#endif
