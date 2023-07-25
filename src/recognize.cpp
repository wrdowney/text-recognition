#include <tesseract/baseapi.h>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    try {
        std::unique_ptr<tesseract::TessBaseAPI> tess(new tesseract::TessBaseAPI());
        tess->Init(nullptr, "eng");
        tess->SetVariable("user_defined_dpi", "70");

        for (int i = 1; i < argc; ++i) {
            const std::string fn = argv[i];
            std::cout << "loading " << fn << std::endl;

            cv::Mat mat = cv::imread(fn);
            tess->SetImage(mat.data, mat.cols, mat.rows, mat.channels(), mat.step1());

            const auto *text = tess->GetUTF8Text();
            if (text == nullptr) throw std::invalid_argument("failed to detect any text");
            const std::string str = text;
            delete [] text;

            std::cout << str << std::endl;

            cv::imshow("mat", mat);
            const auto key = cv::waitKey();
            if (key == 27) break;
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
