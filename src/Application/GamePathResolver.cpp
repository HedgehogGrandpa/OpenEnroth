#include "GamePathResolver.h"

#include "Library/Logger/Logger.h"
#include "Library/Environment/Interface/Environment.h"

namespace {
    struct PathResolutionConfig {
        std::string_view overrideEnvKey;
        std::initializer_list<std::string_view> registryKeys;
    };

    constexpr PathResolutionConfig mm6Config {
        mm6PathOverrideKey,
        {
            "HKEY_LOCAL_MACHINE/SOFTWARE/GOG.com/Games/1207661253/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/GOG.com/GOGMM6/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/New World Computing/Might and Magic\xC2\xAE VI/1.0/AppPath", // \xC2\xAE is (R) in utf-8.
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/GOG.com/Games/1207661253/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/GOG.com/GOGMM6/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/New World Computing/Might and Magic\xC2\xAE VI/1.0/AppPath"
        }
	};


    constexpr PathResolutionConfig mm7Config {
        mm7PathOverrideKey,
        {
            "HKEY_LOCAL_MACHINE/SOFTWARE/GOG.com/Games/1207658916/Path",
            "HKEY_LOCAL_MACHINE/SOFTWARE/GOG.com/GOGMM7/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/New World Computing/Might and Magic VII/1.0/AppPath",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/GOG.com/Games/1207658916/Path",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/GOG.com/GOGMM7/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/New World Computing/Might and Magic VII/1.0/AppPath"
        }
    };


    constexpr PathResolutionConfig mm8Config {
        mm8PathOverrideKey,
        {
            "HKEY_LOCAL_MACHINE/SOFTWARE/GOG.com/GOGMM8/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/New World Computing/Might and Magic Day of the Destroyer/1.0/AppPath",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/GOG.com/GOGMM8/PATH",
            "HKEY_LOCAL_MACHINE/SOFTWARE/WOW6432Node/New World Computing/Might and Magic Day of the Destroyer/1.0/AppPath"
        }
    };


    std::vector<std::string> resolvePaths(const Environment &environment, const PathResolutionConfig& config) {
        // If we have a path override then it'll be the only path we'll check.
        std::string envPath = environment.getenv(config.overrideEnvKey);
        if (!envPath.empty()) {
            logger->info("Path override provided, '{}={}'.", config.overrideEnvKey, envPath);
            return { envPath };
        }

        std::vector<std::string> result;

        // Otherwise we check PWD first.
        result.push_back(".");

        // Then we check paths from registry on Windows,...
        for (const auto& registryKey : config.registryKeys) {
            std::string registryPath = environment.queryRegistry(registryKey);
            if (!registryPath.empty())
                result.push_back(registryPath);
        }

        // ...Android storage paths on Android,...
        std::string externalPath = environment.path(PATH_ANDROID_STORAGE_EXTERNAL);
        if (!externalPath.empty())
            result.push_back(externalPath);
        std::string internalPath = environment.path(PATH_ANDROID_STORAGE_INTERNAL);
        if (!internalPath.empty())
            result.push_back(internalPath);
        // TODO(captainurist): need a mechanism to show user-visible errors. Commenting out for now.
        //if (ANDROID && result.empty())
        //    platform->showMessageBox("Device currently unsupported", "Your device doesn't have any storage so it is unsupported!");

        // ...or Library/Application Support in home on macOS.
#ifdef __APPLE__
        std::string home = environment.path(PATH_HOME);
        if (!home.empty())
            result.push_back(home + "/Library/Application Support/OpenEnroth");
#endif

        return result;
    }
}

std::vector<std::string> resolveMm6Paths(Environment *environment) {
    return resolvePaths(*environment, mm6Config);
}

std::vector<std::string> resolveMm7Paths(Environment *environment) {
    return resolvePaths(*environment, mm7Config);
}

std::vector<std::string> resolveMm8Paths(Environment *environment) {
    return resolvePaths(*environment, mm8Config);
}
