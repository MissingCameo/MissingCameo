#pragma once

#include <format>
#include <memory>
#include <string>

#include <windows.h>

namespace minono::missing_cameo
{
    class missing_cameo
    {
    public:
        static missing_cameo &get_instance()
        {
            static missing_cameo instance;
            return instance;
        }

        template <typename... Args>
        void log(std::string_view &&format, Args &&...args)
        {
            SYSTEMTIME local_time;
            GetLocalTime(&local_time);
            std::string log_text = std::format(
                "[{:04d}/{:02d}/{:02d} {:02d}:{:02d}:{:02d}.{:03d}] {}\r\n",
                local_time.wYear, local_time.wMonth, local_time.wDay,
                local_time.wHour, local_time.wMinute, local_time.wSecond, local_time.wMilliseconds,
                std::vformat(format, std::make_format_args(args...)));
            if (_log_file != nullptr)
            {
                DWORD written;
                WriteFile(
                    _log_file.get(),
                    log_text.data(),
                    static_cast<DWORD>(log_text.size()),
                    &written,
                    nullptr);
            }
        }

        constexpr void set_module_handle(const HINSTANCE &handle)
        {
            _handle = handle;
        }

        constexpr const HINSTANCE &get_module_handle()
        {
            return _handle;
        }

    private:
        missing_cameo()
            : _log_file(std::unique_ptr<void, void (*)(void *)>(CreateFileW(
                                                                    L"missing_cameo.log",
                                                                    GENERIC_WRITE,
                                                                    FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr),
                                                                reinterpret_cast<void (*)(void *)>(CloseHandle)))
        {
            if (_log_file != nullptr)
            {
                SetFilePointer(_log_file.get(), 0, 0, FILE_END);
            }

#if defined(DEBUG)
            log("You are using a debug version of MissingCameo, the performance would be poor.");
#endif
        }
        virtual ~missing_cameo() = default;

        missing_cameo(const missing_cameo &) = delete;
        missing_cameo(missing_cameo &&) = delete;
        missing_cameo &operator=(const missing_cameo &) = delete;
        missing_cameo &operator=(missing_cameo &&) = delete;

        std::unique_ptr<void, void (*)(void *)> _log_file;
        HINSTANCE _handle;
    };
}
