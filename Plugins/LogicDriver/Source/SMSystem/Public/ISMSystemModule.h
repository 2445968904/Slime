// Copyright Recursoft LLC 2019-2022. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#define LD_PLUGIN_NAME "SMSystem"
#define LOGICDRIVER_RUNTIME_MODULE_NAME "SMSystem"

/**
 * The public interface to this module
 */
class ISMSystemModule : public IModuleInterface
{
public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static ISMSystemModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ISMSystemModule>(LOGICDRIVER_RUNTIME_MODULE_NAME);
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded(LOGICDRIVER_RUNTIME_MODULE_NAME);
	}
};
