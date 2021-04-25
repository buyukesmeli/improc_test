#ifndef INC_LCD_IMAGE_SHOW_H_
#define INC_LCD_IMAGE_SHOW_H_

#include "stm32f7xx_hal.h"
#include "image.h"
#include "main.h"
#include "dma2d.h"

void imshow_rgb888(Image* img, LTDC_LayerCfgTypeDef * lcd_layer);
void imshow_gray8(Image* img,  LTDC_LayerCfgTypeDef * lcd_layer);
void imshow_gray_f32(Image* img, LTDC_LayerCfgTypeDef * lcd_layer);
#endif
