// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
#include "emu.h"
#include "teleprinter.h"

#include "screen.h"
#include "speaker.h"


static const uint8_t teleprinter_font[128*8] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,
	0x38,0x38,0x38,0x38,0x00,0x00,0x00,0x00,
	0x3f,0x3f,0x3f,0x3f,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x38,0x38,0x38,0x38,0x07,0x07,0x07,0x07,
	0x3f,0x3f,0x3f,0x3f,0x07,0x07,0x07,0x07,
	0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x38,
	0x07,0x07,0x07,0x07,0x38,0x38,0x38,0x38,
	0x38,0x38,0x38,0x38,0x38,0x38,0x38,0x38,
	0x3f,0x3f,0x3f,0x3f,0x38,0x38,0x38,0x38,
	0x00,0x00,0x00,0x00,0x3f,0x3f,0x3f,0x3f,
	0x07,0x07,0x07,0x07,0x3f,0x3f,0x3f,0x3f,
	0x38,0x38,0x38,0x38,0x3f,0x3f,0x3f,0x3f,
	0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,
	0x00,0x00,0x00,0x00,0x2a,0x15,0x2a,0x15,
	0x2a,0x15,0x2a,0x15,0x00,0x00,0x00,0x00,
	0x3f,0x3f,0x3f,0x3f,0x2a,0x15,0x2a,0x15,
	0x2a,0x15,0x2a,0x15,0x3f,0x3f,0x3f,0x3f,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x00,
	0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00,
	0x14,0x14,0x3e,0x14,0x3e,0x14,0x14,0x00,
	0x08,0x3c,0x0a,0x1c,0x28,0x1e,0x08,0x00,
	0x06,0x26,0x10,0x08,0x04,0x32,0x30,0x00,
	0x08,0x14,0x14,0x0c,0x2a,0x12,0x2c,0x00,
	0x08,0x08,0x04,0x00,0x00,0x00,0x00,0x00,
	0x10,0x08,0x04,0x04,0x04,0x08,0x10,0x00,
	0x04,0x08,0x10,0x10,0x10,0x08,0x04,0x00,
	0x00,0x08,0x2a,0x1c,0x2a,0x08,0x00,0x00,
	0x00,0x08,0x08,0x3e,0x08,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x08,0x04,0x00,
	0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,
	0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00,
	0x1c,0x22,0x32,0x2a,0x26,0x22,0x1c,0x00,
	0x08,0x0c,0x08,0x08,0x08,0x08,0x1c,0x00,
	0x1c,0x22,0x20,0x18,0x04,0x02,0x3e,0x00,
	0x3e,0x20,0x10,0x18,0x20,0x22,0x1c,0x00,
	0x10,0x18,0x14,0x12,0x3e,0x10,0x10,0x00,
	0x3e,0x02,0x1e,0x20,0x20,0x22,0x1c,0x00,
	0x10,0x08,0x04,0x1c,0x22,0x22,0x1c,0x00,
	0x3e,0x20,0x10,0x08,0x04,0x04,0x04,0x00,
	0x1c,0x22,0x22,0x1c,0x22,0x22,0x1c,0x00,
	0x1c,0x22,0x22,0x1c,0x10,0x08,0x04,0x00,
	0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x00,
	0x00,0x00,0x08,0x00,0x08,0x08,0x04,0x00,
	0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x00,
	0x00,0x00,0x3e,0x00,0x3e,0x00,0x00,0x00,
	0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x00,
	0x1c,0x22,0x20,0x10,0x08,0x00,0x08,0x00,
	0x1c,0x22,0x32,0x2a,0x3a,0x02,0x3c,0x00,
	0x08,0x14,0x22,0x22,0x3e,0x22,0x22,0x00,
	0x1e,0x22,0x22,0x1e,0x22,0x22,0x1e,0x00,
	0x1c,0x22,0x02,0x02,0x02,0x22,0x1c,0x00,
	0x1e,0x24,0x24,0x24,0x24,0x24,0x1e,0x00,
	0x3e,0x02,0x02,0x1e,0x02,0x02,0x3e,0x00,
	0x3e,0x02,0x02,0x1e,0x02,0x02,0x02,0x00,
	0x1c,0x22,0x02,0x02,0x32,0x22,0x3c,0x00,
	0x22,0x22,0x22,0x3e,0x22,0x22,0x22,0x00,
	0x1c,0x08,0x08,0x08,0x08,0x08,0x1c,0x00,
	0x38,0x10,0x10,0x10,0x10,0x12,0x0c,0x00,
	0x22,0x12,0x0a,0x06,0x0a,0x12,0x22,0x00,
	0x02,0x02,0x02,0x02,0x02,0x02,0x3e,0x00,
	0x22,0x36,0x2a,0x2a,0x22,0x22,0x22,0x00,
	0x22,0x22,0x26,0x2a,0x32,0x22,0x22,0x00,
	0x1c,0x22,0x22,0x22,0x22,0x22,0x1c,0x00,
	0x1e,0x22,0x22,0x1e,0x02,0x02,0x02,0x00,
	0x1c,0x22,0x22,0x22,0x2a,0x12,0x2c,0x00,
	0x1e,0x22,0x22,0x1e,0x0a,0x12,0x22,0x00,
	0x1c,0x22,0x02,0x1c,0x20,0x22,0x1c,0x00,
	0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
	0x22,0x22,0x22,0x22,0x22,0x22,0x1c,0x00,
	0x22,0x22,0x22,0x14,0x14,0x08,0x08,0x00,
	0x22,0x22,0x22,0x2a,0x2a,0x2a,0x14,0x00,
	0x22,0x22,0x14,0x08,0x14,0x22,0x22,0x00,
	0x22,0x22,0x22,0x14,0x08,0x08,0x08,0x00,
	0x3e,0x20,0x10,0x08,0x04,0x02,0x3e,0x00,
	0x0e,0x02,0x02,0x02,0x02,0x02,0x0e,0x00,
	0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00,
	0x38,0x20,0x20,0x20,0x20,0x20,0x38,0x00,
	0x08,0x1c,0x2a,0x08,0x08,0x08,0x08,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,
	0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1c,0x20,0x3c,0x22,0x3c,0x00,
	0x02,0x02,0x1e,0x22,0x22,0x22,0x1e,0x00,
	0x00,0x00,0x3c,0x02,0x02,0x02,0x3c,0x00,
	0x20,0x20,0x3c,0x22,0x22,0x22,0x3c,0x00,
	0x00,0x00,0x1c,0x22,0x3e,0x02,0x1c,0x00,
	0x18,0x04,0x0e,0x04,0x04,0x04,0x04,0x00,
	0x00,0x00,0x3c,0x22,0x22,0x3c,0x20,0x18,
	0x02,0x02,0x1e,0x22,0x22,0x22,0x22,0x00,
	0x08,0x00,0x0c,0x08,0x08,0x08,0x1c,0x00,
	0x10,0x00,0x18,0x10,0x10,0x10,0x12,0x0c,
	0x02,0x02,0x22,0x12,0x0e,0x16,0x22,0x00,
	0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x00,
	0x00,0x00,0x16,0x2a,0x2a,0x2a,0x2a,0x00,
	0x00,0x00,0x1a,0x26,0x22,0x22,0x22,0x00,
	0x00,0x00,0x1c,0x22,0x22,0x22,0x1c,0x00,
	0x00,0x00,0x1e,0x22,0x22,0x1e,0x02,0x02,
	0x00,0x00,0x3c,0x22,0x22,0x3c,0x20,0x20,
	0x00,0x00,0x34,0x0c,0x04,0x04,0x04,0x00,
	0x00,0x00,0x3c,0x02,0x1c,0x20,0x1e,0x00,
	0x08,0x08,0x1c,0x08,0x08,0x08,0x10,0x00,
	0x00,0x00,0x22,0x22,0x22,0x32,0x2c,0x00,
	0x00,0x00,0x22,0x22,0x22,0x14,0x08,0x00,
	0x00,0x00,0x22,0x22,0x2a,0x2a,0x14,0x00,
	0x00,0x00,0x22,0x14,0x08,0x14,0x22,0x00,
	0x00,0x00,0x22,0x22,0x14,0x08,0x04,0x02,
	0x00,0x00,0x3e,0x10,0x08,0x04,0x3e,0x00,
	0x10,0x08,0x08,0x04,0x08,0x08,0x10,0x00,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
	0x04,0x08,0x08,0x10,0x08,0x08,0x04,0x00,
	0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x2a,0x15,0x2a,0x15,0x2a,0x15,0x2a,0x15
};

teleprinter_device::teleprinter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: generic_terminal_device(mconfig, TELEPRINTER, tag, owner, clock, WIDTH, HEIGHT)
{
}

void teleprinter_device::scroll_line()
{
	memmove(m_buffer.get(), m_buffer.get() + m_width, (m_height-1) * m_width);
	memset(m_buffer.get() + m_width * (m_height-1), 0x20, m_width);
}

void teleprinter_device::write_char(uint8_t data) {
	m_buffer[(m_height-1)*m_width+m_x_pos] = data;
	m_x_pos++;
	if (m_x_pos >= m_width)
	{
		m_x_pos = 0;
		scroll_line();
	}
}

void teleprinter_device::clear() {
	memset(m_buffer.get(), 0, m_width*m_height);
	m_x_pos = 0;
}

void teleprinter_device::term_write(uint8_t data)
{
	switch(data) {
		case 10: m_x_pos = 0;
				scroll_line();
				break;
		case 13: m_x_pos = 0; break;
		case  9: m_x_pos = (m_x_pos & 0xf8) + 8;
				if (m_x_pos >= m_width)
					m_x_pos = m_width-1;

				break;
		case 16: break;
		default: write_char(data); break;
	}
}

/***************************************************************************
    VIDEO HARDWARE
***************************************************************************/
uint32_t teleprinter_device::tp_update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	uint8_t code;
	int y, c, x, b;

	for (y = 0; y < m_height; y++)
	{
		for (c = 0; c < 8; c++)
		{
			int horpos = 0;
			for (x = 0; x < m_width; x++)
			{
				code = teleprinter_font[(m_buffer[y*m_width + x]  & 0x7f) *8 + c];
				for (b = 0; b < 8; b++)
				{
					bitmap.pix32(y*8 + c, horpos++) =  (code >> b) & 0x01 ? 0 : 0x00ffffff;
				}
			}
		}
	}
	return 0;
}

/***************************************************************************
    VIDEO HARDWARE
***************************************************************************/
void teleprinter_device::device_add_mconfig(machine_config &config)
{
	screen_device &screen(SCREEN(config, TELEPRINTER_SCREEN_TAG, SCREEN_TYPE_RASTER));
	screen.set_refresh_hz(50);
	screen.set_vblank_time(ATTOSECONDS_IN_USEC(2500)); /* not accurate */
	screen.set_size(teleprinter_device::WIDTH*8, teleprinter_device::HEIGHT*8);
	screen.set_visarea(0, teleprinter_device::WIDTH*8-1, 0, teleprinter_device::HEIGHT*8-1);
	screen.set_screen_update(FUNC(teleprinter_device::tp_update));
	generic_keyboard_device &keyboard(GENERIC_KEYBOARD(config, "keyboard", 0));
	keyboard.set_keyboard_callback(FUNC(generic_terminal_device::kbd_put));

	SPEAKER(config, "bell").front_center();
	BEEP(config, "beeper", 2'000).add_route(ALL_OUTPUTS, "bell", 0.50);
}


/*-------------------------------------------------
    device_reset - device-specific reset
-------------------------------------------------*/

void teleprinter_device::device_reset()
{
	clear();
	generic_terminal_device::device_reset();
}

DEFINE_DEVICE_TYPE(TELEPRINTER, teleprinter_device, "teleprinter", "Teleprinter")
