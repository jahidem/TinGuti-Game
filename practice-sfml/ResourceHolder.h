#pragma once
#include"SFML/Graphics.hpp"
#include<assert.h>
#include"enums.h"
#include<iostream>
template<typename Resource, typename Identifier>

class ResourceHolder {
public:
	void load(Identifier id, const std::string& filename) 
	{
		std::unique_ptr<Resource> resource(new Resource);
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("TextHolder::load - Failed to load"
				+ filename);
		auto inserted = mResourceMap.insert(std::make_pair(id, move(resource)));
		assert(inserted.second);
	}
	Resource& get(Identifier id)
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());
		return *found->second;
	}
	const Resource& get(Identifier id) const
	{
		auto found = mResourceMap.find(id);
		return *found->second;
	}

private:
	std::map<Identifier,
		std::unique_ptr<Resource>> mResourceMap;

};