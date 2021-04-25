#include "chapters/chapter8.h"
#include "main.h"
#include "lcd/image_show.h"
#include "image_source/image_source.h"
#include <math.h>

void negation() {
	Image in, out;
	ConfigureImage(&in, (uint8_t*) IMAGE_ADDRESS_1, 128, 128, 1, IMAGE_FORMAT_RGB, IMAGE_DATA_TYPE_UINT8);
	ConfigureImage(&out, (uint8_t*) IMAGE_ADDRESS_2, 128, 128, 1, IMAGE_FORMAT_RGB, IMAGE_DATA_TYPE_UINT8);

	GetFromUART(&in);

	Negate(&in, &out);

	LTDC_LayerCfgTypeDef lcd_layer;
	lcd_layer.FBStartAdress = LCD_FRAME_BUFFER;
	lcd_layer.ImageWidth = 480;
	lcd_layer.ImageHeight = 272;
	lcd_layer.WindowX0 = 0;
	lcd_layer.WindowY0 = 0;

	imshow_rgb888(&in, &lcd_layer);

	lcd_layer.WindowX0 = 130;
	lcd_layer.WindowY0 = 0;

	imshow_rgb888(&out, &lcd_layer);
}

void power_law() {
	Image in, out;
	ConfigureImage(&in, (uint8_t*) IMAGE_ADDRESS_1, 128, 128, 1, IMAGE_FORMAT_RGB, IMAGE_DATA_TYPE_UINT8);
	ConfigureImage(&out, (uint8_t*) IMAGE_ADDRESS_2, 128, 128, 1, IMAGE_FORMAT_RGB, IMAGE_DATA_TYPE_UINT8);

	GetFromUART(&in);

	PowerLaw(&in, 1, 0.5, &out);

	LTDC_LayerCfgTypeDef lcd_layer;
	lcd_layer.FBStartAdress = LCD_FRAME_BUFFER;
	lcd_layer.ImageWidth = 480;
	lcd_layer.ImageHeight = 272;
	lcd_layer.WindowX0 = 0;
	lcd_layer.WindowY0 = 0;

	imshow_rgb888(&in, &lcd_layer);

	lcd_layer.WindowX0 = 130;
	lcd_layer.WindowY0 = 0;

	imshow_rgb888(&out, &lcd_layer);
}

void histogram_equalization() {
	Image in, in_gray, out;
	uint32_t in_hist[256];
	uint32_t out_hist[256];

	ConfigureImage(&in, (uint8_t*) IMAGE_ADDRESS_1, 128, 128, 1, IMAGE_FORMAT_RGB, IMAGE_DATA_TYPE_UINT8);
	ConfigureImage(&in_gray, (uint8_t*) IMAGE_ADDRESS_2, 128, 128, 1, IMAGE_FORMAT_MONO, IMAGE_DATA_TYPE_UINT8);
	ConfigureImage(&out, (uint8_t*) IMAGE_ADDRESS_3, 128, 128, 1, IMAGE_FORMAT_RGB, IMAGE_DATA_TYPE_UINT8);

	GetFromUART(&in);

	rgb_to_gray(&in, &in_gray);
	HistogramEqualization(&in_gray, &out);

	LTDC_LayerCfgTypeDef lcd_layer;
	lcd_layer.FBStartAdress = LCD_FRAME_BUFFER;
	lcd_layer.ImageWidth = 480;
	lcd_layer.ImageHeight = 272;
	lcd_layer.WindowX0 = 0;
	lcd_layer.WindowY0 = 0;

	imshow_gray8(&in_gray, &lcd_layer);

	lcd_layer.WindowX0 = 130;
	lcd_layer.WindowY0 = 0;

	imshow_gray8(&out, &lcd_layer);

	Histogram(&in_gray,in_hist);
	Histogram(&out,out_hist);
}
