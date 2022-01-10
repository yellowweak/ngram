#include <ngram/searcher.hpp>

void Searcher::loadRecord(){
    wstring wline;
    string csv_path = Config::test_mode? _CSV_CONCATENED_PATH_TEST:_CSV_CONCATENED_PATH;
    Reader FileReader(csv_path);
    while(FileReader.readLine(wline)){
        records.emplace_back(wline);
    }
    logger << L"Loaded " << int_size(records) << L" records." << Logger::endl;
    return;
}