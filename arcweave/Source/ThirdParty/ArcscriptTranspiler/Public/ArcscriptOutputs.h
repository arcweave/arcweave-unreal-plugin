#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Arcweave
{
    class IOutputNode
    {
    public:
        virtual ~IOutputNode() = default;

        virtual std::string GetText() = 0;
        virtual void MergeScriptOutput(std::string text) = 0;
    };

    class IHasParagraphs
    {
    public:
        virtual ~IHasParagraphs() = default;

        virtual void AppendParagraph(std::string text) = 0;
    };

    class Paragraph: public IOutputNode
    {
    private:
        std::string text_;

    public:

        explicit Paragraph(const std::string &text)
        {
            text_ = text;
        }
        
        inline void MergeScriptOutput(std::string text) override
        {
            if (!text.empty()) {
                if (!text_.empty())
                {
                    text_ += ' ' + text;
                } else {
                    text_ = text;
                }
            }
        }

        inline std::string GetText() override
        {
            return "<p>" + text_ + "</p>";
        }
    };

    class Blockquote: public IOutputNode, public IHasParagraphs
    {
    public:
        std::vector<std::unique_ptr<Paragraph>> paragraphs;

        inline void AppendParagraph(std::string text) override
        {
            paragraphs.push_back(std::make_unique<Paragraph>(text));
        }

        inline void MergeScriptOutput(std::string text) override
        {
            if (paragraphs.empty())
            {
                AppendParagraph(text);
                return;
            }
            paragraphs.back()->MergeScriptOutput(text);
        }

        inline std::string GetText() override
        {
            std::string output;
            for (const auto& value : paragraphs)
            {
                output += value->GetText();
            }

            return "<blockquote>" + output + "</blockquote>";
        }
    };
    
    class ArcscriptOutputs: public IHasParagraphs
    {
    private:
        std::vector<std::unique_ptr<IOutputNode>> outputs_;
        IHasParagraphs* current_node_ = nullptr;
        bool added_script_ = false;
    public:
        void AppendParagraph(std::string text) override;
        void AddParagraph(std::string text);
        void AddBlockquote();
        void AddScript();
        void AddScriptOutput(std::string text);
        void ExitBlockquote();
        std::string GetText();
    };
        
}
