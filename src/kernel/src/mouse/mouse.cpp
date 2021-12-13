#include "mouse.h"

void mouseWait()
{
    uint64_t timeout = 100000;
    while(timeout--)
    {
        if((inb(0x64) & 0b10) == 0)
            return;
    }
}

void mouseWaitInput()
{
    uint64_t timeout = 100000;
    while(timeout--)
    {
        if((inb(0x64) & 0b1) )
            return;
    }
}

void mouseWrite(uint8_t value)
{
    mouseWait();
    outb(0x64, 0xD4);
    mouseWait();
    outb(0x60, value);
}

uint8_t mouseRead()
{
    mouseWaitInput();
    return inb(0x60);
}

uint8_t mouseCycle = 0;
uint8_t mousePackets[4]; // the mouse sends data in 3 packets of 8 bits (1 byte) optionaly can be configured for 4 bytes for scrollwheel information and 4th and 5th mouse button
bool packetReady = false;
Point mousePosition;
void handleMouse(uint8_t data)
{
    switch (mouseCycle)
    {
    case 0:
        if(packetReady) break;
        if(data & 0b00001000 == 0) break;
        mousePackets[0] = data;
        mouseCycle++;
        break;
    
    case 1:
        if(packetReady) break;
        mousePackets[1] = data;
        mouseCycle++;
        break;

    case 2:
        if(packetReady) break;
        mousePackets[2] = data;
        packetReady = true;
        mouseCycle = 0; 
        break;
    }
}

void processMousePacket()
{
    if(!packetReady) return;
    packetReady = false;

    bool leftBtn = mousePackets[0] & PS2LeftBtn ? true : false;
    bool rightBtn = mousePackets[0] & PS2RightBtn ? true : false;
    bool middleBtn = mousePackets[0] & PS2MiddleBtn ? true : false;

    bool xOverflow = mousePackets[0] & PS2XOverflow ? true : false;
    bool yOverflow = mousePackets[0] & PS2YOverflow ? true : false;
    bool xSign = mousePackets[0] & PS2XSign ? true : false;
    bool ySign = mousePackets[0] & PS2YSign ? true : false;

    if(!xSign)
    {
        mousePosition.X += mousePackets[1]; 
        if(xOverflow)
            mousePosition.X += 255;
    }
    else
    {
        mousePackets[1] = 256 - mousePackets[1];
        mousePosition.X -= mousePackets[1];
        if(xOverflow)
            mousePosition.X -= 255;
    }

    if(!ySign)
    {
        mousePosition.Y -= mousePackets[2]; 
        if(yOverflow)
            mousePosition.Y -= 255;
    }
    else
    {
        mousePackets[2] = 256 - mousePackets[2];
        mousePosition.Y += mousePackets[2];
        if(yOverflow)
            mousePosition.Y += 255;
    }

    if(mousePosition.X < 0) mousePosition.X = 0;
    if(mousePosition.X > GLOBAL_RENDERER->TargetFramebuffer->Width-8) mousePosition.X = GLOBAL_RENDERER->TargetFramebuffer->Width-8;

    if(mousePosition.Y < 0) mousePosition.Y = 0;
    if(mousePosition.Y > GLOBAL_RENDERER->TargetFramebuffer->Height-16) mousePosition.Y = GLOBAL_RENDERER->TargetFramebuffer->Height-16;

    GLOBAL_RENDERER->PutChar('a', mousePosition.X, mousePosition.Y);
}

void PS2Mouse()
{
    outb(0x64, 0xA0); // enable auxilary device - mouse
    mouseWait();
    outb(0x64, 0x20); // tell keyboard command wnts to be sent to keyboard
    mouseWaitInput();
    uint8_t status = inb(0x60);
    status |= 0xb10;
    mouseWait();
    outb(0x64, 0x60);
    mouseWait();

    mouseWrite(0xF6);
    mouseRead();

    mouseWrite(0xF4);
    mouseRead();
}