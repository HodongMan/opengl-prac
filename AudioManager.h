#pragma once

#include <string>
#include <vector>

class Point;
class Sound;


class AudioManager
{
public:

	static void init( const std::vector<std::string>& source ) noexcept;

	static double progress( void ) noexcept;
};