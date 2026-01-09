/*===========================================================================*/
/**
 * @file image_processing.cpp
 *
 *------------------------------------------------------------------------------
 * Copyright (c) 2025 - Pablo Joaquim
 * MIT License: https://opensource.org/licenses/MIT
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 * Playground to develop and try several computer vision and image processing use cases
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
 * Header Files
 *===========================================================================*/
#include <opencv2/opencv.hpp>
#include <iostream>

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
#define NDEBUG

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Local Object Declarations
 *===========================================================================*/

/*===========================================================================*
 * Local Variables Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/
/*****************************************************************************
 * Name         opencv_test
 * Description  Do some tests with the opencv library
 *****************************************************************************/
int opencv_test()
{
    // OpenCV reads the image into a 2D matrix where every element is a pixel in BGR format
    cv::Mat img = cv::imread("build/lenna.png");

    if (img.empty())
    {
        std::cout << "Error detected while reading the image" << std::endl;
        return -1;
    }

    std::cout << "Size: " << img.cols << " x " << img.rows << std::endl;
    std::cout << "Channels: " << img.channels() << std::endl;
    std::cout << "Type: " << img.type() << std::endl;

    // Vec3b is a type defined in OpenCV which represents a vector of 3 bytes (like pixel[3])
    // img.at returns the information of the pixel at (row, col) position
    cv::Vec3b pixel = img.at<cv::Vec3b>(100, 100);
    std::cout << "B=" << (int)pixel[0] << std::endl
              << "G=" << (int)pixel[1] << std::endl
              << "R=" << (int)pixel[2] << std::endl;

    // Show the image
    cv::imshow("OpenCV en WSL", img);
    cv::waitKey(0);

    // Grayscale conversion (this is very useful for objects and borders detection)
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); // cvtColor: convert between color spaces
    cv::imshow("Gray", gray);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}
