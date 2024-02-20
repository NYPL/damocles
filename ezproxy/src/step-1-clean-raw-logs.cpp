
#include "main.h"

using namespace std;
using namespace rang;
using namespace indicators;



constexpr auto LOG_LOC {"./logs/i.ezproxy.nypl.org.2024-*.log"};

static ProgressBar bar{
        option::BarWidth{70},
        option::Start{"["},
        option::Fill{"■"},
        option::Lead{"■"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PostfixText{""},
        option::ForegroundColor{Color::yellow},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
};


const string display_time() noexcept {
    string ret {fmt::format("[{}] ", to_string(time(0)))};
    return ret;
}

void handle_sigint(const int signum) {
    if (signum != 2)
        throw runtime_error {"received unhandled signal"};
    indicators::show_console_cursor(true);
    cerr << "\n" << fg::red << display_time() << "caught SIGINT\n"
         << style::reset << endl;
    exit(1);
}

const vector<string> get_files() noexcept {
    vector<string> input_files;
    input_files.reserve(366);
    for (const auto& p : glob::glob(LOG_LOC)) {
        input_files.push_back(p);
        #ifdef SAMPLE
        // if (input_files.size() > 2) break;
        if (input_files.size() > 25) break;
        #endif
    }
    sort(input_files.begin(), input_files.end());
    // remove last (incomplete log)
    // if (input_files.size() < 365) // TODO: leap years?
    if (input_files.size() < 366) // 2024 is a leap year
        input_files.pop_back();
    return input_files;
}

void process_line(string* all_fields, const string& line) noexcept {
    uint8_t counter {0};
    string item {};
    stringstream ss {line};

    while (std::getline(ss, item, ' ')) {
        all_fields[counter] = move(item);
        ++counter;
        if (counter > 6)
            return;
    }
}

const string fix_whole_date(const string& adate) noexcept {
    struct tm tm{};
    strptime(adate.c_str(), "[%d/%b/%Y:%T", &tm);
    char datestring[20] {0};
    strftime(datestring, 20, "%F %T", &tm);
    string ret {datestring};
    return ret;
}

const char* get_small_url(string fullurl) {
    const auto urlsize   { fullurl.size() };
    char* cfullurl       { const_cast<char*>(fullurl.c_str()) };
    char* starting_point { static_cast<char*>(memrchr(cfullurl, '/', 10)) };
    if (starting_point==nullptr)
        throw std::runtime_error {fmt::format("URL string ({}) malformed", fullurl)};
    starting_point++;
    char* ending_point { static_cast<char*>(memchr(starting_point, ':', urlsize-10)) };
    if (ending_point==nullptr)
        throw std::runtime_error {fmt::format("URL string ({}) malformed", fullurl)};
    *ending_point = '\0';
    // special case for "58122.on.worldcat.org" (and possibly more)
    if (isdigit(starting_point[0])) {
        char* new_starting_p { static_cast<char*>(memchr(starting_point, '.', urlsize-10)) };
        if (isdigit(*(new_starting_p-1)))
            starting_point = new_starting_p+1;
    }
    return starting_point;
}

int main() {

    signal(SIGINT, handle_sigint);

    cout << "\n\n" << fg::gray << style::dim
         << display_time() << "::alice glass:: HI!\n" << style::reset
         << style::bold << fg::cyan << display_time()
         << "Processing raw logs\n" << style::reset << endl;

    const vector<string> input_files { get_files() };
    const auto count                 { input_files.size() };
    const string last_date           { input_files[count-1].substr(24, 10) };
    uint32_t counter                 { 0 };
    const string output_file {fmt::format("intermediate/cleaned-logs-{}.dat", last_date)};

    FILE* outfile { fopen(output_file.c_str(), "w") };
    fmt::print(outfile, "{}\t{}\t{}\t{}\t{}\t{}\n",
               "ip", "barcode", "session", "date_and_time", "url", "fullurl");

    // reusing this to store the necessary fields
    string tmp[7] {};

    show_console_cursor(false);

    for (const auto& item : input_files) {
        ++counter;
        const auto perc { static_cast<size_t>(std::round(counter*100/count)) };
        bar.set_option(option::PostfixText{
                fmt::format("  {}/{}  {}%", counter, count, perc) });
        bar.set_progress(perc);

    #ifndef IOSTREAMINPUT
        char* line    {nullptr};
        size_t size   {0};
        ssize_t read  {0};
        FILE* infile  { fopen(item.c_str(), "r") };
        const auto fd { fileno(infile) };
        posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
        while ((read = getline(&line, &size, infile)) != -1) {
    #else
        ifstream infile {item};
        string line {};
        while (std::getline(infile, line)) {
    #endif
            process_line(tmp, line);

            string barcode  { move(tmp[1]) }; if (barcode == "-") continue;
            string ip       { move(tmp[0]) };
            string sessionp { move(tmp[2]) };
            string date     { fix_whole_date(move(tmp[3])) };
            string fullurl  { move(tmp[6]) };
            string url      { get_small_url(fullurl) };

            fmt::print(outfile, "{}\t{}\t{}\t{}\t{}\t{}\n",
                       ip, barcode, sessionp, date, url, fullurl);
        }
    #ifndef IOSTREAMINPUT
        fclose(infile);
    #endif
    }

    show_console_cursor(true);
    cout << style::bold << fg::green << display_time() << "Done!"
         << style::reset << fg::reset << endl;
}

