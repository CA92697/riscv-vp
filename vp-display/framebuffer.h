#pragma once
#include <inttypes.h>
#include <cassert>
#include <cstring>

#define SHMKEY 1338
static constexpr uint16_t screenWidth = 800;
static constexpr uint16_t screenHeight = 600;


typedef uint16_t Color;

struct Point
{
	float x;
	float y;
	Point() : x(0), y(0){};
	Point(float x, float y) : x(x), y(y){};
};

struct Frame
{
    Color raw[screenHeight][screenWidth];   //Notice: Screen is on side
};

struct Framebuffer
{
    uint8_t activeFrame;
    enum class Command : uint8_t
    {
        none = 0,
        clearAll,
        fillBackground,
        fillInactiveFrame,
        applyFrame,
    } volatile command;
    union Parameter
    {
    	struct
    	{
    		Color color;
    	} fill;
    	struct
    	{
    		Point from;
    		Point to;
    	} line;
    	inline Parameter(){};
    } parameter;
    Frame frames[2];
    Frame background;

    Framebuffer() : activeFrame(0), command(Command::none){};

    Frame& getActiveFrame()
    {
        return frames[activeFrame % 2];
    }
    Frame& getInactiveFrame()
    {
        return frames[(activeFrame + 1) % 2];
    }
    Frame& getBackground()
    {
        return background;
    }
};
