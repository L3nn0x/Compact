#ifndef MYHIGHLIGHT_H
#define MYHIGHLIGHT_H

#include <QSyntaxHighlighter>
#include <QList>
#include "verif.h"

class MyHighlight : public QSyntaxHighlighter
{
    Q_OBJECT

        public:
            enum Construct {
                Entity,
                Reg,
                Bra,
                Number,
                Comment,
                Label,
                LastConstruct=Label
            };

            MyHighlight(QTextDocument *document);
            ~MyHighlight();

            void setFormatFor(Construct construct,const QTextCharFormat &format);
            QTextCharFormat formatFor(Construct construct) const
                { return m_formats[construct]; }

        protected:
            void highlightBlock(const QString &text);

        private:
            enum State{
                NormalState=-1
            };

            QTextCharFormat m_formats[LastConstruct + 1];
};

#endif // MYHIGHLIGHT_H
