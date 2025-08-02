#include "RegexDefine.h"

const QString RegexDefine::EMAIL_PATTERN = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

const QString RegexDefine::PHONE_PATTERN = "^1[3-9]\\d{9}$";

const QString RegexDefine::IPV4_PATTERN = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

const QString RegexDefine::NUMBER_PATTERN = "^[0-9]+$";

const QString RegexDefine::LETTER_PATTERN = "^[a-zA-Z]+$";

const QString RegexDefine::ALPHANUMERIC_PATTERN = "^[a-zA-Z0-9]+$";

const QString RegexDefine::URL_PATTERN = "^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$";

const QString RegexDefine::DATE_PATTERN = "^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$";

const QString RegexDefine::TIME_PATTERN = "^([01]\\d|2[0-3]):[0-5]\\d:[0-5]\\d$";

const QString RegexDefine::PASSWORD_PATTERN = "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$"; 