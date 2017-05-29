#include "AssetManager.h"

std::map<std::string, std::function<Asset* ()>> AssetManager::m_factories;

void AssetManager::Bind(const std::string & name, std::function<Asset*()> factory)
{
	m_factories[name] = factory;
}

void AssetManager::Unbind(const std::string & name)
{
	auto it = m_factories.find(name);
	if (it != m_factories.end()) {
		m_factories.erase(it);
	}
}

void AssetManager::Clear()
{
	m_factories.clear();
}


// Texture asset
TextureFactory::TextureFactory(const std::string & path) :
	m_path(path), m_asset(nullptr)
{
}

Asset * TextureFactory::Load()
{
	if (m_asset == nullptr) {
		std::shared_ptr<TextureAsset> asset = std::make_shared<TextureAsset>();
		if (asset->m_texture.loadFromFile(m_path)) {
			m_asset = std::move(asset);
		}
		else {
			throw std::runtime_error("unable to load texture: \"" + m_path + "\"");
		}
	}

	return m_asset.get();
}


// Animation asset
AnimationFactory::AnimationFactory(const Animation & animation) :
	m_asset(nullptr)
{
	m_asset = std::shared_ptr<AnimationAsset>();
	m_asset->m_animation = animation;
}

Asset * AnimationFactory::Load()
{
	if (m_asset == nullptr) {
		// TODO: сделать загрузку из файла
	}

	return m_asset.get();
}
