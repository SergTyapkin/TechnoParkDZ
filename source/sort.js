'use strict';

/* компаратор для обработки буквы 'Ё' - она по неизвестным причинам "больше" любой буквы,
а потому если нам надо сравнить с 'Ё', вместо этого сравниваем с 'Ж', разбирая случай, когда обе буквы равны.
 */
let comparator = function(a, b) {
    a = a.toLowerCase();
    b = b.toLowerCase();
    if (a === 'ё') {
        if (b === 'ё')
            return 0;
        else if (b >= 'ж')
            return -1;
        else
            return 1;
    } else if (b === 'ё') {
        if (a >= 'ж')
            return 1;
        else
            return -1;
    } else {
        return (b<a) - (a<b); // стандартное сравнение, на выходе: -1 / 0 / 1
    }
}

const sort = function (string) {
    if (!string.length) return null;

    let lastId = 0;
    let word, sentence = [];
    string += ' ';
    for (let i = 0; i < string.length; i++) {
        if (string[i] == ' ') { // идём до первого пробела
            word = string.substring(lastId, i).split(''); // берём слово до этого пробела в виде массива
            lastId = i + 1;
            word.sort(comparator); // сортируем буквы в слове
            if (word.length) {
                sentence.push(word[0].toUpperCase()); // первая буква - заглавная
                for (let c = 1; c < word.length; c++) {
                    sentence[sentence.length - 1] += word[c].toLowerCase(); // остальные - строчные
                }
            }
            word = [];
        }
    }
    sentence.sort(comparator); // сортируем слова
    return sentence.join(' ');
};