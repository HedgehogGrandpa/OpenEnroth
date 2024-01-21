#pragma once

#include <memory>
#include <functional>

#include "GameStarterOptions.h"

class Platform;
class Environment;
class Logger;
class BufferLogSink;
class LogSink;
class PlatformApplication;
class GameConfig;
class Renderer;
class Nuklear;
class Engine;
class Game;
class EngineController;

class GameStarter {
 public:
    explicit GameStarter(GameStarterOptions options);
    ~GameStarter();

    PlatformApplication *application() const {
        return _application.get();
    }

    GameConfig *config() const {
        return _config.get();
    }

    void run();

    void runInstrumented(std::function<void(EngineController *)> controlRoutine);

 private:
    GameStarterOptions _options;
    std::unique_ptr<Environment> _environment;
    std::unique_ptr<BufferLogSink> _bufferLogSink;
    std::unique_ptr<LogSink> _defaultLogSink;
    std::unique_ptr<Logger> _logger;
    std::shared_ptr<GameConfig> _config;
    std::unique_ptr<Platform> _platform;
    std::unique_ptr<PlatformApplication> _application;
    std::unique_ptr<Renderer> _renderer;
    std::unique_ptr<Nuklear> _nuklear;
    std::unique_ptr<Engine> _engine;
    std::shared_ptr<Game> _game;
};
