#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

/*===========================================================================*/
/**
 * @file image_processing.h
 *
 *------------------------------------------------------------------------------
 * Copyright (c) 2025 - Pablo Joaquim
 * MIT License: https://opensource.org/licenses/MIT
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION: API for the functions of the image_processing module
 *
 * @todo Add full description here
 *
 * @section ABBR ABBREVIATIONS:
 *   - @todo List any abbreviations, precede each with a dash ('-').
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - @todo Update list of design document(s).
 *
 *   - Requirements Document(s):
 *     - @todo Update list of requirements document(s)
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - @todo Update list of other applicable standards
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files (Common to C and C++)
 *===========================================================================*/
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
/*===========================================================================*
 * Header Files (C++ only)
 *===========================================================================*/
#endif

/*===========================================================================*
 * Exported Preprocessor #define Constants
 *===========================================================================*/

/*===========================================================================*
 * Exported Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Classes (C++ only)
 *===========================================================================*/
#ifdef __cplusplus
// @todo: Add C++ class declarations here.
#endif

/*===========================================================================*
 * Exported C Function Prototypes
 *===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
// @todo: Add pure C function prototypes here.

#ifdef __cplusplus
} /* extern "C" */
#endif

 /*===========================================================================*
 * Exported C++ Function Prototypes
 *===========================================================================*/
#ifdef __cplusplus
// @todo: Add pure C++ function prototypes here.

/*****************************************************************************
 * @fn         img_ImagePlayground
 * @brief      Playground to do some tests with the openCV library
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
 int img_ImagePlayground();

/*****************************************************************************
 * @fn         img_ElemsCounter
 * @brief      Count elements in an image using OpenCV library
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
 int img_ElemsCounter();

/*****************************************************************************
 * @fn         img_VideoPlayground
 * @brief      Play a video using the openCV library
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_VideoPlayground();

/*****************************************************************************
 * @fn         img_DrawingShapes
 * @brief      Drawing shapes by hand
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_DrawingShapes();

/*****************************************************************************
 * @fn         img_DotsDetector
 * @brief      Detect and count the number of dots in an image using OpenCV library
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
 int img_DotsDetector();

/*****************************************************************************
 * @fn         img_MouseEvents
 * @brief      Detect a mouse click event and paint the pixels on that coordinate
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_MouseEvents();

/*****************************************************************************
 * @fn         img_ColorPalette
 * @brief      Show a window with the color palette and trackbars to change it
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_ColorPalette();

/*****************************************************************************
 * @fn         img_ReverseVideoReproduction
 * @brief      Play a video in reverse
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_ReverseVideoReproduction();

/*****************************************************************************
 * @fn         img_CropImage
 * @brief      Crop an image using the mouse to select the region
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_CropImage();

/*****************************************************************************
 * @fn         img_OCR
 * @brief      Perform an OCR over an image using the Tesseract library
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_OCR();

/*****************************************************************************
 * @fn         img_TemplateMatching
 * @brief      Perform a template matching. This is useful for simple objet 
 *             with no scaling or rotation. The template comparisson is px by px.
 *             This is useful for simple applications like logo detection in boxes,
 *             screws positions detection, etc.
 * @param [in] None
 * @return     0-OK, -1-Error
 ******************************************************************************/
int img_TemplateMatching();

#endif /* __cplusplus */

/*===========================================================================*/
/*===========================================================================*/
#endif /* KATAS_H */