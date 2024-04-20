#pragma once

template <typename... Args>
std::string MakeString(Args... args)
{
    std::ostringstream oss;
    (oss << ... << args);
    return oss.str();
}