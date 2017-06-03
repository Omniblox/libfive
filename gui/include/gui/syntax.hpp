#pragma once

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QPlainTextEdit>

class Syntax : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    Syntax(QTextDocument* doc, const QSet<QString>& keywords);
    void matchParens(QTextEdit* text, int cursor_pos);

protected:
    QPoint matchedParen(int pos);

    int searchLeft(int pos);
    int searchRight(int pos);

    void highlightBlock(const QString& text) override;

    /*  Define states to keep track of multiline strings. */
    enum State { BASE = -1, STRING = 1 };

    /*  Structure to use as a rule when highlighting    */
    struct Rule
    {
        Rule() {}
        Rule(QString r, QTextCharFormat f, State si=BASE, State so=BASE,
             int capture=0)
            : regex(QRegularExpression(r)), format(f), state_in(si), state_out(so),
              capture(capture)
        { /* Nothing to do here */ }

        QRegularExpression regex;
        QTextCharFormat format;
        State state_in, state_out;
        int capture;
    };
    QList<Rule> rules;
    QTextCharFormat parens_highlight;
};
