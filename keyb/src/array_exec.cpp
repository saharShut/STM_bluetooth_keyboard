/*
 * array_exec.c
 *
 *  Created on: 22 нояб. 2022 г.
 *      Author: User
 */

#include "array_exec.h"
#include "key_codes.h"

#define START_BYTE 0xDE
#define ARRAY_SIZE 6
#define PHANTOM_STATE 0x01

uint8_t *ArrayExecutor::convert_array(std::list<uint8_t> array)
{
	uint8_t modifier{0}; // Modifier byte
	    uint8_t output[9];
	    std::list<uint8_t> sendList;
	    bool fnPressed{ true };

	    for (uint8_t item : array)
	    {
	        switch (item)
	        {
	        case KEY_LEFTCTRL:
	            modifier |= KEY_MOD_LCTRL; //do something with modifier byte
	            break;
	        case KEY_LEFTSHIFT:
	        	modifier |= KEY_MOD_LSHIFT;
	        	break;
	        case KEY_LEFTALT:
	        	modifier |= KEY_MOD_LALT;
	        	break;
	        case KEY_LEFTMETA:
	        	modifier |= KEY_MOD_LMETA;
	        	break;
	        case KEY_RIGHTCTRL:
	        	modifier |= KEY_MOD_RCTRL;
	        	break;
	        case KEY_RIGHTSHIFT:
	        	modifier |= KEY_MOD_RSHIFT;
	        	break;
	        case KEY_RIGHTALT:
	        	modifier |= KEY_MOD_RALT;
	        	break;
	        case KEY_RIGHTMETA:
	        	modifier |= KEY_MOD_RMETA;
	        	break;
	        case KEY_A:
	        case KEY_B:
	        case KEY_C:
	        case KEY_D:
	        case KEY_E:
	        case KEY_F:
	        case KEY_G:
	        case KEY_H:
	        case KEY_I:
	        case KEY_J:
	        case KEY_K:
	        case KEY_L:
	        case KEY_M:
	        case KEY_N:
	        case KEY_O:
	        case KEY_P:
	        case KEY_Q:
	        case KEY_R:
	        case KEY_S:
	        case KEY_T:
	        case KEY_U:
	        case KEY_V:
	        case KEY_W:
	        case KEY_X:
	        case KEY_Y:
	        case KEY_Z:
	        case KEY_0:
	        case KEY_1:
	        case KEY_2:
	        case KEY_3:
	        case KEY_4:
	        case KEY_5:
	        case KEY_6:
	        case KEY_7:
	        case KEY_8:
	        case KEY_9:
	        case KEY_VOLUMEUP: // any non modifier bytes
	        case KEY_PROPS:
	        case KEY_PAUSE:
	        case KEY_PAGEUP:
	        case KEY_KP0:
	        case KEY_KP1:
	        case KEY_KP2:
	        case KEY_KP3:
	        case KEY_KP4:
	        case KEY_KP5:
	        case KEY_KP6:
	        case KEY_KP7:
	        case KEY_KP9:
	        case KEY_KPENTER:
	        case KEY_POWER:
	        case KEY_MEDIA_PREVIOUSSONG:
	        case KEY_MEDIA_REFRESH:
	        case KEY_KPMINUS:
	        case KEY_NUMLOCK:
	        case KEY_MEDIA_EDIT:
	        case KEY_MEDIA_STOP:
	        case KEY_SPACE:
	        case KEY_KPPLUS:
	        case KEY_GRAVE:
	        case KEY_ESC:
	        case KEY_MEDIA_PLAYPAUSE:
	        case KEY_CAPSLOCK:
	        case KEY_KPEQUAL:
	        case KEY_END:
	        case KEY_MEDIA_FORWARD:
	        case KEY_MEDIA_VOLUMEDOWN:
	        case KEY_TAB:
	        case KEY_SYSRQ:
	        case KEY_COMMA:
	        case KEY_F1:
	        case KEY_F2:
	        case KEY_F3:
	        case KEY_F4:
	        case KEY_F5:
	        case KEY_F6:
	        case KEY_F7:
	        case KEY_F8:
	        case KEY_F9:
	        case KEY_F10:
	        case KEY_F11:
	        case KEY_F13:
	        case KEY_F14:
	        case KEY_F15:
	        case KEY_F12:
	        case KEY_MEDIA_MUTE:
	        case KEY_KPASTERISK:
	        case KEY_BACKSPACE:
	        case KEY_102ND:
	        case KEY_INSERT:
	        case KEY_HOME:
	        case KEY_KPSLASH:
	        case KEY_KPDOT:
	        case KEY_PAGEDOWN:
	        case KEY_SLASH:
	        case KEY_MINUS:
	        case KEY_UP:
	        case KEY_DOWN:
	        case KEY_RIGHT:
	        case KEY_LEFT:
	        case KEY_SEMICOLON:
	        case KEY_ENTER:
	        case KEY_DOT:
	        case KEY_APOSTROPHE:
	        case KEY_RIGHTBRACE:
	        case KEY_LEFTBRACE:
	            sendList.push_front(item);
	            break;
	        case 0xA5:
	        	fnPressed = true;
	        	break;
	        default:
	            break;
	        }
	    }

	    if (sendList.size() > ARRAY_SIZE)
	    {
	        // Phantom state (more then 6 Keys pressed simultaneously
	        sendList.clear();
	        for (int i = 0; i < ARRAY_SIZE; i++)
	        {
	            sendList.push_front(PHANTOM_STATE);
	        }
	    } else
	    {
	        for (int i = sendList.size(); i < ARRAY_SIZE; i++)
	        {
	            sendList.push_back(0x00);
	        }
	    }

	    output[0] = START_BYTE;
	    output[1] = modifier;
	    output[2] = 0x00;
	    int i = 3;
	    for (uint8_t elem : sendList)
	    {
	        output[i++] = elem;
	    }

	    return output;
}


