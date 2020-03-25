#include <iostream>
#include <unistd.h>

int main() {
    std::cout << "Hacking NASA server..." << std::endl;
    for (int i=0; i<=100; i+=10) {
        std::cout << "Progress: " << i << "%" << std::endl;
        sleep(1);
    }
    std::cout << "Hacking completed!" << std::endl;
    sleep(2);
    system("clear");

    std::cout << "\nTOP SECRET DOCUMENT" << std::endl;
    sleep(2);
    std::cout << "\n- zig_zag_Earth.rtf" << std::endl;
    sleep(1);
    std::cout << "\n- Neko_Anime_Girl_Experiment_report.rtf" << std::endl;
    sleep(1);
    std::cout << "\n- Iluminasi_project.rtf" << std::endl;
    sleep(1);
    std::cout << "\n- soal_UAS_struktur_data_UM_2020.pdf" << std::endl;
    std::cout << "\n>> ";
    std::cin.get();

    return 0;
}