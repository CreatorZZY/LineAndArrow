/*
 * @Author: George Zhao
 * @Date: 2020-03-16 15:16:27
 * @LastEditors: George Zhao
 * @LastEditTime: 2020-09-20 21:18:54
 * @Description: 
 * @Email: 2018221138@email.szu.edu.cn
 * @Company: SZU
 * @Version: 1.0
 */
#include "SDK/Dataloader/SDK_Dataloader.hpp"
#include "SDK/Drawer/SDK_Drawer.hpp"
#include "cmdline.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

namespace {

auto initFolder(const std::string& tmp_dirpath = "./", const std::string& data_dirpath = "./")
{
    std::map<std::string, std::string> ph_of_dir;

    ph_of_dir["data"] = data_dirpath + "/data/";
    ph_of_dir["setting"] = data_dirpath + "/setting/";
    ph_of_dir["out"] = data_dirpath + "/out/";
    ph_of_dir["tmp"] = tmp_dirpath + "/tmp/";
    ph_of_dir["OutImg"] = ph_of_dir["out"] + "/img/";

    for (auto& i : ph_of_dir) {
        if (std::filesystem::exists(std::filesystem::path(i.second)) == false) {
            std::filesystem::create_directory(i.second);
        }
    }
    return ph_of_dir;
}

}

decltype(initFolder()) all_path;

int main(int argc, char** argv)
{
    std::cout << "\033[1;33m _     _             ___      _" << std::endl
              << "| |   (_)_ __   ___ ( _ )    / \\   _ __ _ __ _____      __" << std::endl
              << "| |   | | '_ \\ / _ \\/ _ \\/\\ / _ \\ | '__| '__/ _ \\ \\ /\\ / /" << std::endl
              << "| |___| | | | |  __/ (_>  </ ___ \\| |  | | | (_) \\ V  V /" << std::endl
              << "|_____|_|_| |_|\\___|\\___/\\/_/   \\_\\_|  |_|  \\___/ \\_/\\_/" << std::endl
              << "\033[0m" << std::endl;

    std::cout << "\033[1;34m     ____           ____" << std::endl
              << "    | __ ) _   _   / ___| ___  ___  _ __ __ _  ___" << std::endl
              << "    |  _ \\| | | | | |  _ / _ \\/ _ \\| '__/ _` |/ _ \\" << std::endl
              << "    | |_) | |_| | | |_| |  __/ (_) | | | (_| |  __/" << std::endl
              << "    |____/ \\__, |  \\____|\\___|\\___/|_|  \\__, |\\___|" << std::endl
              << "           |___/                        |___/" << std::endl
              << "\033[0m" << std::endl;
    cmdline::parser cmdconfig;
    cmdconfig.set_program_name("LineAndArrow");
    cmdconfig.add<std::string>("input", 'i', "Path to Input File", true);
    cmdconfig.add<std::string>("output", 'o', "Name of Output.", true);
    cmdconfig.add("stdout", 's', "Print SVG in STDOUT.");

    cmdconfig.add<std::string>("datapath", '\000', "Get rsa Key", false, "./");
    cmdconfig.add<std::string>("tmppath", '\000', "Get rsa Key", false, "./");
    cmdconfig.parse_check(argc, argv);
    all_path = initFolder(cmdconfig.get<std::string>("tmppath"), cmdconfig.get<std::string>("datapath"));

    std::filesystem::path stra(all_path["OutImg"]);
    if (std::filesystem::exists(stra) == false)
        std::filesystem::create_directory(stra);
    cr::cairo_surface_t* surfacepng = cr::cairo_image_surface_create(cr::CAIRO_FORMAT_ARGB32, SDK_Draw::PageW, SDK_Draw::PageH);

    std::string filemane = std::string(all_path["OutImg"]) + cmdconfig.get<std::string>("output");
    cr::cairo_surface_t* surfacepdf = cr::cairo_pdf_surface_create((filemane + ".pdf").c_str(), SDK_Draw::PageW, SDK_Draw::PageH);
    cr::cairo_surface_t* surfacesvg = cr::cairo_svg_surface_create((filemane + ".svg").c_str(), SDK_Draw::PageW, SDK_Draw::PageH);

    SDK_Draw::make_line(surfacepng, SDK_Core::NormalColor::GRy);
    SDK_Draw::make_line(surfacepdf, SDK_Core::NormalColor::GRy);
    SDK_Draw::make_line(surfacesvg, SDK_Core::NormalColor::GRy);

    std::filesystem::path strtxt(cmdconfig.get<std::string>("input"));
    if (std::filesystem::exists(strtxt) == false) {
        std::cout << "\033[1;32m" << std::string(cmdconfig.get<std::string>("input")) << " Not exist. \033[0m" << std::endl;
        throw std::logic_error(std::string(cmdconfig.get<std::string>("input")) + std::string(" Not exist."));
    }
    std::vector<SDK_Dataloader::fdata> data = SDK_Dataloader::readdata(cmdconfig.get<std::string>("input"));
    auto a = SDK_Dataloader::normalize_data(data);

    for (const auto& element : a) {
        SDK_Draw::arrow(surfacepng, element.startpoint, element.endpoint, element.color, SDK_Core::SIZE2D({ SDK_Draw::PageW, SDK_Draw::PageH }), 20);
        SDK_Draw::annotate(surfacepng, (element.startpoint + element.endpoint) / 2, SDK_Core::SIZE2D({ SDK_Draw::PageW, SDK_Draw::PageH }), element.name.c_str(), 20, SDK_Draw::UpandDown(element.startpoint, element.endpoint));
        SDK_Draw::arrow(surfacepdf, element.startpoint, element.endpoint, element.color, SDK_Core::SIZE2D({ SDK_Draw::PageW, SDK_Draw::PageH }), 20);
        SDK_Draw::annotate(surfacepdf, (element.startpoint + element.endpoint) / 2, SDK_Core::SIZE2D({ SDK_Draw::PageW, SDK_Draw::PageH }), element.name.c_str(), 20, SDK_Draw::UpandDown(element.startpoint, element.endpoint));
        SDK_Draw::arrow(surfacesvg, element.startpoint, element.endpoint, element.color, SDK_Core::SIZE2D({ SDK_Draw::PageW, SDK_Draw::PageH }), 20);
        SDK_Draw::annotate(surfacesvg, (element.startpoint + element.endpoint) / 2, SDK_Core::SIZE2D({ SDK_Draw::PageW, SDK_Draw::PageH }), element.name.c_str(), 20, SDK_Draw::UpandDown(element.startpoint, element.endpoint));
    }

    cr::cairo_surface_write_to_png(surfacepng, (filemane + ".png").c_str());
    cr::cairo_surface_destroy(surfacepng);
    cr::cairo_surface_destroy(surfacepdf);
    cr::cairo_surface_destroy(surfacesvg);

    return 0;
}
