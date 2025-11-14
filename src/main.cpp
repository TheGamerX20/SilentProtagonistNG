#include <pch.h>

// Patches
#include <SilentProtagonist.h>

namespace Main
{
    // Config Options
    static REX::INI::Bool iSilentProtagonistPatch{ "Patches"sv, "EnableSilentProtagonist"sv, true };

    F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
    {
        // Init
        F4SE::Init(a_f4se);
        REX::INFO("Silent Protagonist NG Initializing...");

        // Load the Config
        const auto config = REX::INI::SettingStore::GetSingleton();
        config->Init("Data/F4SE/Plugins/SilentProtagonistNG.ini", "Data/F4SE/Plugins/SilentProtagonistNGCustom.ini");
        config->Load();

        // Install Silent Protagonist
        if (iSilentProtagonistPatch.GetValue() == true)
        {
            if (SilentProtagonist::Install(a_f4se))
            {
                REX::INFO("Silent Protagonist NG Initialized!");
            }
        }

        // Finished
        return true;
    }
}
