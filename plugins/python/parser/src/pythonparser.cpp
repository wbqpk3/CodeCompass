#include <pythonparser/pythonparser.h>
#include <boost/filesystem.hpp>
#include <util/logutil.h>
#include <memory>

namespace cc
{
namespace parser
{

PythonParser::PythonParser(ParserContext& ctx_): AbstractParser(ctx_)
{
}

bool PythonParser::accept(const std::string& path_)
{
  std::string ext = boost::filesystem::extension(path_);
  return ext == ".py";
}

bool PythonParser::parse()
{
  for(std::string path : _ctx.options["input"].as<std::vector<std::string>>())
  {
    if(boost::filesystem::is_directory(path))
    {
      util::iterateDirectoryRecursive(path, [this](const std::string& currPath_)
      {
        if (boost::filesystem::is_regular_file(currPath_) && accept(currPath_))
        {
            LOG(info) << "PythonParser parse path: " << currPath_;

            model::FilePtr pyfile = _ctx.srcMgr.getFile(currPath_);
            pyfile->parseStatus = model::File::ParseStatus::PSFullyParsed;
            pyfile->type = "PY";
            _ctx.srcMgr.updateFile(*pyfile);
        }

        return true;
      });
    }
  }
  return true;
}

PythonParser::~PythonParser()
{
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern "C"
{
  boost::program_options::options_description getOptions()
  {
    boost::program_options::options_description description("Python Plugin");

    return description;
  }

  std::shared_ptr<PythonParser> make(ParserContext& ctx_)
  {
    return std::make_shared<PythonParser>(ctx_);
  }
}
#pragma clang diagnostic pop

} // parser
} // cc
