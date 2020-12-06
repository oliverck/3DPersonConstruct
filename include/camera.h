#include <astra/astra.hpp>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <jsonxx/json.hpp>

class MultiFrameListener : public astra::FrameListener
{
public:
    MultiFrameListener(int width,int length, bool isTrainCapture);
    ~MultiFrameListener();
private:

    virtual void on_frame_ready(astra::StreamReader& reader,
        astra::Frame& frame) override;
    void process_depth(const astra::DepthFrame& depthFrame);
    void process_rgb(const astra::ColorFrame& colorFrame);
    void process_body_3d(const astra::BodyFrame& bodyFrame, const astra::DepthFrame& deepthFrame);
    void write_video(cv::VideoWriter &writer,cv::Mat frame,cv::Size s, bool valid);
    void write_body(std::ofstream& f, jsonxx::json j);
    

    using duration_type = std::chrono::duration<float>;
    float frameDuration_{ 0.0 };
    using clock_type = std::chrono::system_clock;
    std::chrono::time_point<clock_type> lastTimepoint_{ clock_type::now() };

    cv::VideoWriter videoRgbOutput;
    cv::VideoWriter vidroDepthOutput;
    std::ofstream jointPosOutput;

    bool isTrainCapture;
    bool captureValid;

    int bodyFrameBeginIdx = 0;

    PointDataWindow pointDataWindow;
};