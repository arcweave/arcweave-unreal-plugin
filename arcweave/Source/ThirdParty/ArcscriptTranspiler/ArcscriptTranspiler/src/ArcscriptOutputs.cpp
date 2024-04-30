#include "ArcscriptOutputs.h"

void Arcweave::ArcscriptOutputs::AppendParagraph(std::string text)
{
    outputs_.push_back(std::make_unique<Paragraph>(text));
}

void Arcweave::ArcscriptOutputs::AddParagraph(std::string text)
{
    if (current_node_ == nullptr)
    {
        current_node_ = this;
    }

    if (added_script_)
    {
        if (!outputs_.empty() && dynamic_cast<Blockquote*>(outputs_.back().get()) && dynamic_cast<Blockquote*>(current_node_) == nullptr)
        {
            AppendParagraph(text);
        } else
        {
            AddScriptOutput(text);
        }
        added_script_ = false;
        return;
    }
    current_node_->AppendParagraph(text);
}

void Arcweave::ArcscriptOutputs::AddBlockquote()
{
    if (added_script_ && !outputs_.empty())
    {
        IOutputNode* n = outputs_.back().get();
        if (dynamic_cast<Blockquote*>(n))
        {
            current_node_ = dynamic_cast<IHasParagraphs*>(n);
            return;
        }
    }
    Blockquote* b = new Blockquote();
    outputs_.push_back(std::unique_ptr<IOutputNode>(b));
    current_node_ = b;
}

void Arcweave::ArcscriptOutputs::AddScript()
{
    added_script_ = true;
}


void Arcweave::ArcscriptOutputs::AddScriptOutput(std::string text)
{
    added_script_ = true;
    if (outputs_.empty())
    {
        outputs_.push_back(std::make_unique<Paragraph>(text));
        return;
    }
    outputs_.back()->MergeScriptOutput(text);
}

void Arcweave::ArcscriptOutputs::ExitBlockquote()
{
    current_node_ = this;
}

std::string Arcweave::ArcscriptOutputs::GetText()
{
    std::string output;
    for (const auto& value : outputs_)
    {
        output += value->GetText();
    }

    return output;
}


