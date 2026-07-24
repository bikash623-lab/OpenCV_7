#include <iostream>
#include <onnxruntime/onnxruntime_cxx_api.h>

int main(){
    // initialize ONNX Runtime enviroment
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNXTest");

    // Session options
    Ort::SessionOptions sessionOptions;
    sessionOptions.SetIntraOpNumThreads(1);

    std::cout << "ONNX Runtime initialized successfully!\n";
    std::cout << "Version: " << Ort::GetApiBase()->GetVersionString() << "\n";

    return 0;
}