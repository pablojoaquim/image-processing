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
 * Name         drawHistogram
 * Description  Draw a histogram into a canvas with labels in the axis
 *****************************************************************************/
static void drawHistogram(const cv::Mat &hist, int histSize, cv::Scalar color, const std::string &windowName)
{
    // ========================
    // Histogram normalization
    // ========================
    int hist_w = 600;
    int hist_h = 400;
    int margin = 50;
    cv::normalize(hist, hist, 0, hist_h, cv::NORM_MINMAX);

    // ========================
    // Create the canvas
    // ========================
    cv::Mat histImage(
        hist_h + 2 * margin,
        hist_w + 2 * margin,
        CV_8UC3,
        cv::Scalar(30, 30, 30));

    // ========================
    // Draw the axis
    // ========================
    // Y axis
    cv::line(
        histImage,
        cv::Point(margin, margin),
        cv::Point(margin, margin + hist_h),
        cv::Scalar(200, 200, 200),
        2);

    // X axis
    cv::line(
        histImage,
        cv::Point(margin, margin + hist_h),
        cv::Point(margin + hist_w, margin + hist_h),
        cv::Scalar(200, 200, 200),
        2);

    // ========================
    // Add labels to the axes
    // ========================
    cv::putText(
        histImage,
        "Intensity (0 - 255)",
        cv::Point(margin + hist_w / 2 - 90, margin + hist_h + 40),
        cv::FONT_HERSHEY_SIMPLEX,
        0.5,
        cv::Scalar(220, 220, 220),
        1);

    cv::putText(
        histImage,
        "Pixel count",
        cv::Point(5, margin - 10),
        cv::FONT_HERSHEY_SIMPLEX,
        0.5,
        cv::Scalar(220, 220, 220),
        1);

    // ========================
    // Add ticks to the axes
    // ========================
    int bin_w = cvRound((double)hist_w / histSize);

    for (int i = 0; i <= 255; i += 50)
    {
        int x = margin + i * bin_w;

        cv::line(
            histImage,
            cv::Point(x, margin + hist_h),
            cv::Point(x, margin + hist_h + 5),
            cv::Scalar(200, 200, 200),
            1);

        cv::putText(
            histImage,
            std::to_string(i),
            cv::Point(x - 10, margin + hist_h + 20),
            cv::FONT_HERSHEY_SIMPLEX,
            0.4,
            cv::Scalar(200, 200, 200),
            1);
    }

    // ========================
    // Draw the histogram
    // ========================
    for (int i = 1; i < histSize; i++)
    {
        cv::line(
            histImage,
            cv::Point(
                margin + (i - 1) * bin_w,
                margin + hist_h - cvRound(hist.at<float>(i - 1))),
            cv::Point(
                margin + i * bin_w,
                margin + hist_h - cvRound(hist.at<float>(i))),
            color,
            2);
    }

    // ========================
    // Show the histogram
    // ========================
    cv::imshow(windowName, histImage);
}

/*****************************************************************************
 * Name         img_ImagePlayground
 * Description  Do some tests with images using the opencv library
 *****************************************************************************/
int img_ImagePlayground()
{
    // =========================
    // Image reading
    // =========================
    // OpenCV reads the image into a 2D matrix where every element is a pixel in BGR format
    cv::Mat img = cv::imread("build/pils.png");

    if (img.empty())
    {
        std::cout << "Error detected while reading the image" << std::endl;
        return -1;
    }

    std::cout << "Image info: " << std::endl;
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

    // =========================
    // Grayscale conversion (this is very useful for objects and borders detection)
    // =========================
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); // cvtColor: convert between color spaces
    std::cout << "Gray Image info: " << std::endl;
    std::cout << "Size: " << gray.cols << " x " << gray.rows << std::endl;
    std::cout << "Channels: " << gray.channels() << std::endl;
    std::cout << "Type: " << gray.type() << std::endl;
    // cv::imshow("Gray", gray);
    // cv::waitKey(0);

    // =========================
    // // Binary conversion
    // =========================
    cv::Mat binary;
    // For every pixel, the same threshold value is applied. If the pixel value is
    // smaller than or equal to the threshold, it is set to 0, otherwise it is set to a maximum value
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);
    std::cout << "Binary Image info: " << std::endl;
    std::cout << "Size: " << binary.cols << " x " << binary.rows << std::endl;
    std::cout << "Channels: " << binary.channels() << std::endl;
    std::cout << "Type: " << binary.type() << std::endl;
    // cv::imshow("Binary", binary);
    // cv::waitKey(0);

    // Binary conversion with the best threshold according to the histogram of the image
    cv::Mat binaryOtsu;
    cv::threshold(gray, binaryOtsu, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    std::cout << "Binary Otsu Image info: " << std::endl;
    std::cout << "Size: " << binaryOtsu.cols << " x " << binaryOtsu.rows << std::endl;
    std::cout << "Channels: " << binaryOtsu.channels() << std::endl;
    std::cout << "Type: " << binaryOtsu.type() << std::endl;
    // cv::imshow("Binary Otsu", binaryOtsu);
    // cv::waitKey(0);

    // =========================
    // Noise reduction with GaussianBlur
    // =========================
    cv::Mat blurred;
    // This function takes a kernel and a standard deviation, which means how many pixels
    // in vert and horiz is going to expand the color detected with the kernel.
    // The most common is leave this parameter as 0 and OpenCV is going to calculate the
    // optimal value according to the kernel size.
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0, 0);
    // cv::imshow("Blurred", blurred);
    // cv::waitKey(0);

    // =========================
    // Edges detection (typical proces is Color -> Gray -> Blur -> Edges)
    // =========================
    cv::Mat edges;
    // The function finds edges in the input image and marks them in the output map
    // edges using the Canny algorithm. The smallest value between threshold1 and
    // threshold2 is used for edge linking. The largest value is used to find initial
    // segments of strong edges.
    cv::Canny(blurred, edges, 50, 150);
    // cv::imshow("Edges", edges);
    // cv::waitKey(0);

    // =========================
    // Translation + Rotation + Scaling
    // =========================
    cv::Point2f center(img.cols / 2.0f, img.rows / 2.0f);
    double angle = 45.0;
    double scale = 1.0;
    int tx = 100; // move right 100 pixels
    int ty = 50;  // move down 50 pixels

    // Create the rotation matrix
    cv::Mat M = cv::getRotationMatrix2D(center, angle, scale);
    M.at<double>(0,2) += tx;
    M.at<double>(1,2) += ty;

    // Apply the operations
    cv::Mat imgMoved;
    cv::warpAffine(img, imgMoved, M, img.size());
    cv::imshow("Moved", imgMoved);
    cv::waitKey(0);

    // =========================
    // Histogram
    // =========================
    // Count pixels of a determined color in the whole image and fill a vector with this information
    int histSize = 256;       // bins
    float range[] = {0, 256}; // possible values
    const float *histRange = {range};
    cv::Mat hist;
    cv::calcHist(
        &gray,     // source image
        1,         // image count
        0,         // channel (0 = grey)
        cv::Mat(), // mask (empty)
        hist,      // output
        1,         // dimmension of the histogram
        &histSize, // bins number
        &histRange // range
    );
    cv::Scalar colorGray(128, 128, 128);
    drawHistogram(hist, histSize, colorGray, "Histogram");
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Split channels
    cv::Mat channels[3];
    cv::split(img, channels);
    cv::Mat &b = channels[0];
    cv::Mat &g = channels[1];
    cv::Mat &r = channels[2];
    cv::Mat histB, histG, histR;

    // Histogram BGR
    cv::calcHist(&b, 1, 0, cv::Mat(), histB, 1, &histSize, &histRange);
    cv::calcHist(&g, 1, 0, cv::Mat(), histG, 1, &histSize, &histRange);
    cv::calcHist(&r, 1, 0, cv::Mat(), histR, 1, &histSize, &histRange);

    cv::Scalar colorB(255, 0, 0);
    cv::Scalar colorG(0, 255, 0);
    cv::Scalar colorR(0, 0, 255);
    drawHistogram(histB, histSize, colorB, "Histogram - Blue");
    drawHistogram(histG, histSize, colorG, "Histogram - Green");
    drawHistogram(histR, histSize, colorR, "Histogram - Red");
    cv::waitKey(0);

    // =========================
    // Contours detection (elements counter)
    // =========================
    // Convert to grayscale
    cv::Mat processed;
    cv::cvtColor(img, processed, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(processed, processed, cv::Size(5, 5), 0);
    // Threshold
    cv::threshold(processed, processed, 200, 255, cv::THRESH_BINARY);
    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(processed, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    std::cout << "Number of contours: " << contours.size() << std::endl;
    // Draw contours
    cv::Mat blank = cv::Mat::zeros(img.size(), CV_8UC3);
    cv::drawContours(blank, contours, -1, cv::Scalar(0, 0, 255), 1);
    cv::imshow("Contours", blank);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

/*****************************************************************************
 * Name         ime_ElemsCounter
 * Description  Count elements in an image
 *****************************************************************************/
int img_ElemsCounter()
{
    // ========================
    // Load the image to process
    // ========================
    // OpenCV reads the image into a 2D matrix where every element is a pixel in BGR format
    cv::Mat img = cv::imread("build/pils.png");
    if (img.empty())
    {
        std::cout << "Error detected while reading the image" << std::endl;
        return -1;
    }
    cv::imshow("Original", img);
    cv::waitKey(0);

    // ========================
    // Grayscale conversion
    // ========================
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); // cvtColor: convert between color spaces
    cv::imshow("Gray", gray);
    cv::waitKey(0);

    // ========================
    // Noise reduction with GaussianBlur
    // ========================
    cv::Mat blurred;
    // This function takes a kernel and a standard deviation, which means how many pixels
    // in vert and horiz is going to expand the color detected with the kernel.
    // The most common is leave this parameter as 0 and OpenCV is going to calculate the
    // optimal value according to the kernel size.
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0, 0);
    cv::imshow("GaussianBlur", blurred);
    cv::waitKey(0);

    // ========================
    // Binary threshold detection
    // ========================
    cv::Mat binaryOtsu;
    cv::threshold(blurred, binaryOtsu, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::imshow("Binary Otsu", binaryOtsu);
    cv::waitKey(0);

    // ========================
    // Morphologycal cleaning
    // ========================
    // Remove some noise and separate the elements
    cv::Mat morphclean;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::morphologyEx(binaryOtsu, morphclean, cv::MORPH_OPEN, kernel);
    cv::imshow("Clean", morphclean);
    cv::waitKey(0);

    // // ========================
    // // Fill the blank areas
    // // ========================
    // cv::Mat filled = morphclean.clone();                     // Binary copy
    // cv::floodFill(filled, cv::Point(0, 0), cv::Scalar(255)); // Flood fill from a corner
    // cv::bitwise_not(filled, filled);                         // Invert
    // morphclean = morphclean | filled;
    // cv::imshow("Image Filled", morphclean);
    // cv::waitKey(0);

    // ========================
    // Find contours
    // ========================
    // std::vector<std::vector<cv::Point>> contours;
    // cv::findContours(morphclean, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // int count = 0;
    // for (const auto &c : contours)
    // {
    //     double area = cv::contourArea(c);
    //     if (area > 50) // Threshold to adjust
    //     {
    //         count++;
    //         cv::drawContours(img, std::vector<std::vector<cv::Point>>{c}, -1, cv::Scalar(0, 255, 0), 2);
    //     }
    // }

    // std::cout << "Objetos detectados: " << count << std::endl;
    // cv::imshow("Result", img);
    // cv::waitKey(0);

    // ========================
    // Find contours
    // ========================
    // Contours are curves joining all continuous points along a boundary
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(morphclean, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // ========================
    // Filter and count valid pills
    // ========================
    int pill_count = 0;
    cv::Mat result = img.clone(); // Clone original for visualization

    // Define size thresholds to filter out noise
    const double MIN_AREA = 500;   // Adjust based on your image
    const double MAX_AREA = 10000; // Adjust based on your image

    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);

        // Filter by area to exclude noise and ensure valid pills
        if (area > MIN_AREA && area < MAX_AREA)
        {
            // Optional: Additional shape filtering
            // Pills are elongated, so check aspect ratio
            cv::RotatedRect rect = cv::minAreaRect(contours[i]);
            float aspect_ratio = std::max(rect.size.width, rect.size.height) /
                                 std::min(rect.size.width, rect.size.height);

            // Pills typically have aspect ratio between 1.5 and 3.5
            if (aspect_ratio > 1.3 && aspect_ratio < 4.0)
            {
                pill_count++;

                // Draw contours and labels for visualization
                cv::drawContours(result, contours, i, cv::Scalar(0, 255, 0), 2);

                // Get centroid for numbering
                cv::Moments m = cv::moments(contours[i]);
                cv::Point center(m.m10 / m.m00, m.m01 / m.m00);
                cv::putText(result, std::to_string(pill_count), center,
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2);
            }
        }
    }

    // ========================
    // Display results
    // ========================
    std::cout << "Number of pills detected: " << pill_count << std::endl;
    cv::putText(result, "Pills: " + std::to_string(pill_count), cv::Point(10, 30),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    cv::imshow("Result", result);
    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}

/*****************************************************************************
 * Name         img_VideoPlayground
 * Description  Testing the video player using openCV
 *****************************************************************************/
int img_VideoPlayground()
{
    double resize_factor = 0.75;

    // Open a video file
    cv::VideoCapture capture("build/video1.mp4");
    // Alternative: webcam
    // cv::VideoCapture capture(0);

    if (!capture.isOpened())
    {
        std::cout << "Error detected while reading the file" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::Mat frameResized;
    while (true)
    {
        bool isTrue = capture.read(frame);

        // Check for frames availability
        if (!isTrue || frame.empty())
        {
            break;
        }

        cv::imshow("Video", frame);

        // --- With the frame is possible to work as it is an image ---

        // Resize the frame input
        cv::resize(frame, frameResized, cv::Size(), resize_factor, resize_factor);
        cv::imshow("Video Resized", frameResized);

        // Player ends if key 'd' is pressed
        if (cv::waitKey(20) == 'd')
        {
            break;
        }
    }

    capture.release();
    cv::destroyAllWindows();

    return 0;
}

/*****************************************************************************
 * Name         img_DrawingShaped
 * Description  Drawing shapes by hand
 *****************************************************************************/
int img_DrawingShaped()
{
    // Create a blank image (500x500, 3 channels, uint8)
    cv::Mat blank = cv::Mat::zeros(500, 500, CV_8UC3);
    cv::imshow("Blank", blank);
    cv::waitKey(0);

    // ==============================
    // Paint the image in certain colors
    // ==============================
    blank(cv::Range(200, 300), cv::Range(300, 400)) = cv::Scalar(0, 0, 255);
    cv::imshow("Red Area", blank);
    cv::waitKey(0);

    // ==============================
    // Draw a rectangle
    // ==============================
    cv::rectangle(blank,
                  cv::Point(0, 0),
                  cv::Point(250, 500),
                  cv::Scalar(0, 255, 0),
                  2);
    cv::imshow("Rectangle 1", blank);
    cv::waitKey(0);

    cv::rectangle(blank,
                  cv::Point(0, 0),
                  cv::Point(blank.cols / 2, blank.rows / 3),
                  cv::Scalar(0, 255, 0),
                  cv::FILLED);
    cv::imshow("Rectangle 2", blank);
    cv::waitKey(0);

    // ==============================
    // Draw a circle
    // ==============================
    cv::circle(blank,
               cv::Point(250, 250),
               40,
               cv::Scalar(0, 0, 255),
               -1);
    cv::imshow("Circle", blank);
    cv::waitKey(0);

    // ==============================
    // Draw a line
    // ==============================
    cv::line(blank,
             cv::Point(20, 20),
             cv::Point(blank.cols / 2, blank.rows / 3),
             cv::Scalar(255, 255, 255),
             3);
    cv::imshow("Line", blank);
    cv::waitKey(0);

    // ==============================
    // Write text on image
    // ==============================
    cv::putText(blank,
                "hello world",
                cv::Point(225, 225),
                cv::FONT_HERSHEY_TRIPLEX,
                1.0,
                cv::Scalar(0, 255, 0),
                2);
    cv::imshow("Text", blank);
    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}