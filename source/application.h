#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <iemulator.h>

// Forward declarations to avoid including SDL headers in the header file
struct SDL_Window;
struct SDL_Renderer;

class Application
{
public:
    static Application& instance()
    {
        static Application instance_;
        return instance_;
    }
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;
    
    bool init(std::unique_ptr<IEmulator> emulator);
    void run();
    void close() noexcept;
private:
    Application();

    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    static constexpr int rectWidth_ = 10;
    static constexpr int margin_ = 1;

    std::unique_ptr<IEmulator> emulator_;
};

#endif // APPLICATION_H
