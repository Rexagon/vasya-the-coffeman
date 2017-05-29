#pragma once

#include <functional>
#include <memory>
#include <string>
#include <map>

class Asset;

class AssetManager
{
public:
	static void Bind(const std::string& name, std::function<Asset* ()> factory);
	static void Unbind(const std::string& name);

	template<class T>
	static T* Get(const std::string& name) {
		auto it = m_factories.find(name);
		if (it == m_factories.end()) {
			return nullptr;
		}
		else {
			return reinterpret_cast<T*>(it->second()->GetData());
		}
	}

	static void Clear();
private:
	static std::map<std::string, std::function<Asset* ()>> m_factories;
};


// Вспомогательные классы
class Asset
{
public:
	virtual ~Asset() {}
	virtual void* GetData() = 0;
};

class AssetFactory
{
public:
	virtual ~AssetFactory() {}
	virtual Asset* Load() = 0;

	Asset* operator()() {
		return Load();
	}
};


// Texture asset
#include <SFML/Graphics/Texture.hpp>

class TextureAsset : public Asset
{
public:
	void* GetData() override {
		return &m_texture;
	}
private:
	friend class TextureFactory;

	sf::Texture m_texture;
};

class TextureFactory : public AssetFactory
{
public:
	TextureFactory(const std::string& path);

	Asset* Load() override;
private:
	std::string m_path;
	std::shared_ptr<TextureAsset> m_asset;
};


// Animation asset
#include "Animation.h"

class AnimationAsset : public Asset
{
public:
	void* GetData() override {
		return &m_animation;
	}
private:
	friend class AnimationFactory;

	Animation m_animation;
};

class AnimationFactory : public AssetFactory
{
public:
	AnimationFactory(const Animation& animation);

	Asset* Load() override;
private:
	std::shared_ptr<AnimationAsset> m_asset;
};