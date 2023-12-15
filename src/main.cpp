#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    rs2::colorizer color_map;
    rs2::colorizer color;
    rs2::pipeline pipe;
    pipe.start();
    cv::namedWindow("depth", cv::WINDOW_AUTOSIZE);

    while (cv::waitKey(1) < 0)
    {
        rs2::frameset data = pipe.wait_for_frames();
        rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
        rs2::frame color_flame = data.get_color_frame().apply_filter(color);
        rs2::depth_frame depth_frame = data.get_depth_frame();
        const int w = depth.as<rs2::video_frame>().get_width();
        const int h = depth.as<rs2::video_frame>().get_height();

        cv::Mat img_depth(cv::Size(w, h), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
        cv::Mat img_color(cv::Size(w, h), CV_8UC3, (void*)color_flame.get_data(), cv::Mat::AUTO_STEP);

        cv::cvtColor(img_color, img_color, cv::COLOR_RGB2BGR);

        cv::imshow("img", img_color);
        cv::imshow("depth", img_depth);

        const int width = depth_frame.get_width();
        const int height = depth_frame.get_height();
        const uint16_t *depth_data = reinterpret_cast<const uint16_t *>(depth_frame.get_data());

        const int x = width / 2;
        const int y = height / 2;
        uint16_t depth_value = depth_data[y * width + x];
        std::cout << "Center depth : " << depth_value << " millimeters" << std::endl;

        uint16_t aver_depth_value = (depth_data[y * width + x - 1] + depth_data[y * width + x] +
                depth_data[y * width + x + 1] + depth_data[y * (width - 1) + x] + depth_data[y * (width + 1) + x]) / 5;
        std::cout << "Average Center depth : " << aver_depth_value << " millimeters" << std::endl;

    }

    return 0;
}
