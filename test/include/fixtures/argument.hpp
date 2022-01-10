#ifndef NGRAM_TEST_INCLUDE_ARGUMENT_HPP
#define NGRAM_TEST_INCLUDE_ARGUMENT_HPP
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "../utils/utils.hpp"
class Argument {
    public:
        int argc;
        char *argv[2]; // 2 for testing one flag
};
class ArgumentTest: public testing::Test, public ngramTesting::Utils {
    protected:
        void SetUp() override {
            no_flag_arg.argc = 1;
            no_flag_arg.argv[0] = binary;
            for(auto flag:availible_flags){
                Argument arg;
                arg.argc = 2;
                arg.argv[0] = binary;
                arg.argv[1] = flag;
                single_flag_arg_set.push_back(arg);
            }

        }
        void TearDown() override {
            #if defined(_WIN32) || defined(__WIN32__)
            // redirect log stream(stdout) to handle output messages after Initializer executing _setmode()
            redirectTestLog(this);
            #endif
        }

        Argument no_flag_arg;
        vector<Argument> single_flag_arg_set;

    private:
        char *binary = (char *)"dummy.exe";
        vector<char*> availible_flags = {
            (char *)"-m=s", (char *)"--mode=silent",
            (char *)"-s=i", (char *)"--sort=id",
            (char *)"-s=h", (char *)"--sort=hit"
        };
        
};

#endif