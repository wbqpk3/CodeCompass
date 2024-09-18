#ifndef CC_SERVICE_PYTHON_DIAGRAM_H
#define CC_SERVICE_PYTHON_DIAGRAM_H

#include <model/pyname.h>
#include <util/graph.h>
#include <service/pythonservice.h>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace cc
{
namespace service
{
namespace language
{
namespace python
{    
  class Diagram {
    public:
      Diagram(
        std::shared_ptr<odb::database> db_,
        std::shared_ptr<std::string> datadir_,
        const cc::webserver::ServerContext& context_);

      util::Graph getFunctionCallDiagram(const model::PYName& pyname);
      util::Graph getModuleDiagram(const core::FileId& fileId);

      enum NodeType {
        FunctionCenterNode,
        FunctionCallNode,
        FunctionCallDefinitionNode,
        FunctionCallerNode,
        FunctionCallerDefinitionNode,
        FilePathNode,
        FilePathCenterNode,
        ImportedNode
      };
    private:
      PythonServiceHandler m_pythonService;
      core::ProjectServiceHandler m_projectService;
      std::map<core::FileId, util::Graph::Subgraph> m_subgraphs;
      void addFunctionNode(util::Graph& graph_, const util::Graph::Node& centerNode, const model::PYName& pyname, const NodeType& nodeType);
      void decorateNode(util::Graph& graph_, util::Graph::Node& node_, const NodeType& nodeType);
      util::Graph::Node addPYNameNode(util::Graph& graph_, const model::PYName& pyname, bool addSubgraph);
      util::Graph::Node addFileNode(util::Graph& graph_, const core::FileInfo& fileInfo);
  };
} // python
} // language
} // service
} // cc

#endif
