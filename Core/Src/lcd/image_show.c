#include "lcd/image_show.h"
#include <string.h>

void imshow_rgb888(Image* img, DMA2D_HandleTypeDef * hdma2d, LTDC_LayerCfgTypeDef * lcd_layer){
	uint32_t frame_buffer = lcd_layer->FBStartAdress + (lcd_layer->WindowY0 * lcd_layer->ImageWidth + lcd_layer->WindowX0)*3;

	hdma2d->Init.Mode         = DMA2D_M2M_PFC;
	hdma2d->Init.ColorMode    = DMA2D_RGB888;
	hdma2d->Init.OutputOffset = lcd_layer->ImageWidth-img->Width;

	/* Foreground Configuration */
	hdma2d->LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d->LayerCfg[1].InputAlpha = 0xFF;
	hdma2d->LayerCfg[1].InputColorMode = CM_RGB888;
	hdma2d->LayerCfg[1].InputOffset = 0;

	hdma2d->Instance = DMA2D;

	/* DMA2D Initialization */
	if(HAL_DMA2D_Init(hdma2d) == HAL_OK) {
		if(HAL_DMA2D_ConfigLayer(hdma2d, 1) == HAL_OK) {
			if (HAL_DMA2D_Start(hdma2d, (uint32_t)img->pData, frame_buffer, img->Width, img->Height) == HAL_OK) {
				/* Polling For DMA transfer */
				HAL_DMA2D_PollForTransfer(hdma2d, 10);
			}
		}
	} else {
		while(1);
	}
}
void imshow_gray8(Image* img, DMA2D_HandleTypeDef * hdma2d, LTDC_LayerCfgTypeDef * lcd_layer){
	int i;
	Image buf_img;
	memcpy(&buf_img,img,sizeof(buf_img));
	for (i=0;i<img->Width*img->Height;i++){
		memcpy((uint8_t *) PROCESS_BUFFER+3*i,img->pData+i,1);
		memcpy((uint8_t *) PROCESS_BUFFER+3*i+1,img->pData+i,1);
		memcpy((uint8_t *) PROCESS_BUFFER+3*i+2,img->pData+i,1);
	}
	buf_img.pData = (uint8_t *) PROCESS_BUFFER;
	imshow_rgb888(&buf_img,hdma2d,lcd_layer);
}

void imshow_gray_f32(Image* img, DMA2D_HandleTypeDef * hdma2d, LTDC_LayerCfgTypeDef * lcd_layer){
	int i;
	uint8_t p;
	Image buf_img;
	memcpy(&buf_img,img,sizeof(buf_img));
	for (i=0;i<img->Width*img->Height;i++){
		p = (uint8_t)READ_AS_FLOAT(img,0,i);
		memcpy((uint8_t *) PROCESS_BUFFER+3*i,&p,1);
		memcpy((uint8_t *) PROCESS_BUFFER+3*i+1,&p,1);
		memcpy((uint8_t *) PROCESS_BUFFER+3*i+2,&p,1);
	}
	buf_img.pData = (uint8_t *) PROCESS_BUFFER;
	imshow_rgb888(&buf_img,hdma2d,lcd_layer);
}
