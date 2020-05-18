const int ARGC = 2;
const std::string ERROR_FILE = "Ошибка открытия файла с названием: ";
const std::string WRONG_ARGC = "Неправильное количество аргументов: miniDictionary.exe <dictionaryFile>";
const std::string INSERT_TRANS = "Введите перевод слова:";
const std::string SAVE_CHANGES = "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
const std::string AGREE_SAVE_L = "y";
const std::string AGREE_SAVE_H = "Y";
const std::string SAVED = "Изменения сохранены. До свидания.";
const std::string UNSAVED = "Изменения не сохранены. До свидания.";
const std::string END_WORK = "...";
const char DELIMETER = '-';

typedef std::map<std::string, std::string> Dictionary;

void ReadDictionary(const std::string& inputFile, Dictionary& dictionary);
bool ProcessInput(Dictionary& dictionary);
bool SearchForTranslation(Dictionary& dictionary, const std::string& searchString);
bool AddTranslation(const std::string& inputWord, Dictionary& dictionary);
bool GetTranslation(const std::string& inputWord, std::string& translation);
void InsertInDictionary(Dictionary& dictionary, const std::string& inputWord, const std::string& translation);
void RecordToFile(const std::string& outputFile, Dictionary& dictionary);
std::string ToLowerCase(std::string inputWord);
std::string ReadLine();