import os

# Mapeamento de Consistência UI
mapping = {
    "UI::RED": "UI::VERMELHO",
    "UI::YELLOW": "UI::AMARELO",
    "UI::CYAN": "UI::CIANO",
    "UI::GREEN": "UI::VERDE",
    "UI::BLUE": "UI::AZUL",
    "UI::BOLD": "UI::NEGRITO",
    "UI::WHITE": "UI::BRANCO"
}

def fix_ui_references():
    count = 0
    for root, dirs, files in os.walk("."):
        if any(x in root for x in ["build", ".git", "target"]):
            continue
            
        for file in files:
            if file.endswith((".cpp", ".h")):
                path = os.path.join(root, file)
                with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                
                new_content = content
                for old, new in mapping.items():
                    new_content = new_content.replace(old, new)
                
                if new_content != content:
                    with open(path, 'w', encoding='utf-8') as f:
                        f.write(new_content)
                    print(f"[FIXED] {path}")
                    count += 1
    print(f"\nTotal de arquivos saneados: {count}")

if __name__ == "__main__":
    fix_ui_references()
