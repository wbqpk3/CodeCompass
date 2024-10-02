from dataclasses import dataclass
from jedi import Project

@dataclass
class ParserConfig:
    root_path: str
    venv_path: str | None = None
    project: Project | None = None 
    debug: bool = True
    safe_env: bool = False
    type_hint: bool = False
    file_refs: bool = True