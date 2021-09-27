#include"ResourceHolder.h"
template <typename Resource, typename Identifier>
void ResourceHolder<typename Resource,
	typename Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("TextHolder::load - Failed to load"
			+ filename);
	auto inserted = mResourceMap.insert(std::make_pair(id, move(resource)));
	assert(inserted.second);
}
template <typename Resource, typename Identifier>
Resource& ResourceHolder<typename Resource,
	typename Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<typename Resource,
	typename Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	return *found->second;
}