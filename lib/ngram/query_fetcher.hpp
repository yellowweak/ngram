#ifndef NGRAM_LIB_NGRAM_QUERY_FETCHER_HPP
#define NGRAM_LIB_NGRAM_QUERY_FETCHER_HPP
#include "../../include/ngram/common.hpp"
#include "reader.hpp"
#include "config.hpp"
class QueryFetcher: public Reader {
    public:
    QueryFetcher(string file_path);
    /**
     * Returns true if can perform next input opertion.
     * Otherwise, returns false for any reason.
     */
    bool fetchOneQuery(wstring& wbuffer);
};

#endif