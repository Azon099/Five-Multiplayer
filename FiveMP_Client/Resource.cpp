/*
* This file is part of the CitizenFX project - http://citizen.re/
*
* See LICENSE and MENTIONS in the root of the source tree for information
* regarding licensing.
*/

#include <StdInc.h>
#include <ResourceImpl.h>
#include <ResourceManagerImpl.h>

//#include <ResourceMetaDataComponent.h>

namespace fx
{
	ResourceImpl::ResourceImpl(const std::string& name, ResourceManagerImpl* manager)
		: m_name(name), m_manager(manager), m_state(ResourceState::Uninitialized)
	{
		OnInitializeInstance(this);
	}
#if 0
	bool ResourceImpl::LoadFrom(const std::string& rootPath)
	{
		fwRefContainer<ResourceMetaDataComponent> metaData = GetComponent<ResourceMetaDataComponent>();

		if (m_state != ResourceState::Uninitialized)
		{
			return true;
		}

		auto retval = metaData->LoadMetaData(rootPath);

		if (retval)
		{
			trace("Resource loading for %s failed:\n%s\n", m_name.c_str(), retval->c_str());
		}

		m_rootPath = rootPath;

		m_state = ResourceState::Stopped;

		return !retval.is_initialized();
	}
#endif
	const std::string& ResourceImpl::GetName()
	{
		return m_name;
	}

	const std::string& ResourceImpl::GetIdentifier()
	{
		return m_name;
	}

	const std::string& ResourceImpl::GetPath()
	{
		return m_rootPath;
	}

	bool ResourceImpl::Start()
	{
		if (!OnStart())
		{
			return false;
		}

		m_state = ResourceState::Started;

		return true;
	}

	bool ResourceImpl::Stop()
	{
		if (!OnStop())
		{
			return false;
		}

		m_state = ResourceState::Stopped;

		return true;
	}

	void ResourceImpl::Tick()
	{
		if (m_state != ResourceState::Started)
		{
			return;
		}

		OnTick();
	}

	void ResourceImpl::Destroy()
	{
		m_state = ResourceState::Uninitialized;

		OnRemove();
	}

	ResourceManager* ResourceImpl::GetManager()
	{
		return m_manager;
	}

	fwEvent<Resource*> Resource::OnInitializeInstance;
}