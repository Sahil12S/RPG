#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

class AssetManager
{
public:
    AssetManager();
    virtual ~AssetManager();

    /**
     * LoadTexture loads texture from file and store in memory
     * 
     * @param name: name to be give to texture
     * @param fileName: name of file of texture to use
     */
    void LoadTexture(const std::string &name, const std::string &fileName);

    /**
     * GetTexture returns textures stored with given name
     * 
     * @param name: name of texture to be fetched from memory
     * @return sf::Texture: sfml Texture object
     */
    sf::Texture &GetTexture(const std::string &name);

    /**
     * LoadFont loads font from file and store in memory
     * 
     * @param name: name to be give to font
     * @param fileName: name of file of font to use
     */
    void LoadFont(const std::string &name, const std::string &fileName);

    /**
     * GetFont returns fonts stored with given name
     * 
     * @param name: name of font to be fetched from memory
     * @return sf::Font: sfml Font object
     */
    sf::Font &GetFont(const std::string &name);

    /**
     * LoadAudio loads audio from file and store in memory
     * 
     * @param name: name to be give to audio
     * @param fileName: name of file of audio to use
     */
    void LoadAudio(const std::string &name, const std::string &fileName);

    /**
     * GetAudio returns sound buffer stored with given name
     * 
     * @param name: name of audio to be fetched from memory
     * @return sf::SoundBuffer: sfml SoundBuffer object
     */
    sf::SoundBuffer &GetAudio(const std::string &name);

private:
    std::map<std::string, sf::Texture> m_Textures;
    std::map<std::string, sf::Font> m_Fonts;
    std::map<std::string, sf::SoundBuffer> m_Audios;
};

#endif // ASSET_MANAGER_HPP