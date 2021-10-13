#include "../../../include/indexer.hpp"

void Indexer::generateConcatenedCsv(){
    Writter FileWritter(_CSV_CONCATENED_PATH);
    for(auto &row:csv){
        for(int i=0; i<int_size(row); i++){
            FileWritter << row[i] << (i==int_size(row)-1? L"\n":L",");
        }
    }
    
    logger << L"Generated " << int_size(csv) << L" lines of concatened csv." << Logger::endl;
    return;
}

void Indexer::mergePrevRecord(vector<wstring> &record, vector<int> target_columns){
    wstring prev, current;
    for(auto &col:target_columns){
        prev = csv.back()[col];
        current = record[col];
        csv.back()[col] = prev.substr(0, int_size(prev)-1) + current.substr(1, int_size(current)-1);
    }
    return;
}

void Indexer::loadCsv(){
    bool between_parentheses=false, merge_mode=false;
    wchar_t delim=L',', left_p=L'（', right_p=L'）';
    wstring wline, cell=L"";
    vector<wstring> record;
    Reader FileReader(_CSV_SOURCE_PATH);

    while(FileReader.readLine(wline)){
        record.clear();
        for(auto &wc:wline){
            if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3 && wc==left_p)  between_parentheses = true;
            if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3 && wc==right_p)  between_parentheses = false;
            
            if(wc==delim){
                record.emplace_back(cell);
                cell=L"";
                if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3+1 && merge_mode)  break;
                if(int_size(record)==_CSV_COLUMN_INDEX_ADDRESS_3 && between_parentheses) merge_mode=true;
            }
            else    cell += wc;
        }
        if(merge_mode){
            vector<int> target_columns = {_CSV_COLUMN_INDEX_ADDRESS_3_PHONETIC,_CSV_COLUMN_INDEX_ADDRESS_3};
            mergePrevRecord(record, target_columns);
            merge_mode = false;
        }
        else{
            record.emplace_back(cell); // last element
            csv.emplace_back(record); // create new record
        }
        cell=L"";
    }

    generateConcatenedCsv();
    return;
}