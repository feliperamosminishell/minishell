<div align="center">

```ascii
╔══════════════════════════════════════════════════════════════════════╗
║   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ║
║   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ║
║   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ║
║   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ║
║   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗║
║   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝║
╚══════════════════════════════════════════════════════════════════════╝
```

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=600&size=22&duration=3000&pause=1000&color=00FF41&center=true&vCenter=true&random=false&width=600&lines=Building+my+own+UNIX+shell;Parsing+%7C+Executing+%7C+Piping;Because+bash+wasn't+mysterious+enough" alt="Typing SVG" />

[![42 Score](https://img.shields.io/badge/Score-125%2F100-success?style=for-the-badge&logo=42&logoColor=white)](https://github.com/feliperamosminishell/minishell)
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)](https://github.com/42School/norminette)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))

</div>

---

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/feliperamosminishell/minishell.git
cd minishell

# Compile
make

# Run
./minishell
minishell> echo "Hello World!"
Hello World!
```

---

## 📊 Interactive Project Tracker

<div align="center">

### 🎯 Overall Progress
```
███████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  9%
```
**Completed:** 1/52 tasks | **Time Invested:** 90h | **Deadline:** March 30, 2026

### ⏱️ Time Progress
```
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  0%  [----------------------------] 
```
**Project Timeline:** Jan 31 → Mar 30, 2026 | **Elapsed:** 0 days | **Remaining:** 58 days

</div>

---

## 📅 Development Phases

### 📝 Phase 1: Parsing & Tokenization
**Deadline:** Feb 14, 2025 | ⚠️ OVERDUE by 377 days| **Status:** ✅ COMPLETED

```
Progress: ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 0%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [X] Lexer implementation
- [X] Token recognition (words, operators, quotes)
- [X] Quote handling (single `'` and double `"`)
- [X] Syntax error detection
- [X] Command splitting by pipes `|`
- [X] Memory leak checks with valgrind

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 18h  
**💡 Key learnings:** State machines, tokenization algorithms  
**🔧 Tools used:** GDB, Valgrind, custom test suite

**Challenges faced:**
- Handling nested quotes correctly
- Managing memory in recursive parsing functions
- Edge cases with empty tokens

</details>

---

### 🔧 Phase 2: Built-in Commands
**Deadline:** Feb 21, 2025 | ⚠️ OVERDUE by 370 days| **Status:** 🚧 IN PROGRESS

```
Progress: █████████████████░░░░░░░░░░░░░░░░░░░░░░░ 43%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [x] `echo` with `-n` flag
- [ ] `cd` with relative and absolute paths
- [x] `pwd` (print working directory)
- [ ] `export` (set environment variables)
- [ ] `unset` (remove environment variables)
- [x] `env` (display environment)
- [ ] `exit` with exit code

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 12h  
**💡 Key learnings:** Environment variable manipulation, getcwd/chdir  
**🔧 Implemented:** All 7 mandatory built-ins

**Challenges faced:**
- Handling cd with no arguments (HOME directory)
- Export with and without values
- Exit with invalid arguments

</details>

---

### ⚙️ Phase 3: Execution & Processes
**Deadline:** Mar 01, 2025 | ⚠️ OVERDUE by 362 days| **Status:** 📋 PLANNED

```
Progress: ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 0%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [ ] PATH resolution
- [ ] Binary execution with `execve`
- [ ] `fork` and process management
- [ ] Exit status handling `$?`
- [ ] Process cleanup and zombie prevention
- [ ] Edge cases with invalid commands

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 22h  
**💡 Key learnings:** fork/exec model, process lifecycle, waitpid  

**What's needed:**
- Proper zombie process handling
- Testing various edge cases
- Signal handling during execution

</details>

---

### 🔀 Phase 4: Pipes & Redirections
**Deadline:** Mar 08, 2025 | ⚠️ OVERDUE by 355 days| **Status:** 📋 PLANNED

```
Progress: ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 0%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [ ] Single pipe `|`
- [ ] Multiple pipes (chain commands)
- [ ] Input redirection `<`
- [ ] Output redirection `>`
- [ ] Append mode `>>`
- [ ] Heredoc `<<` implementation
- [ ] Complex pipe + redirection combos

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 16h  
**💡 Key learnings:** File descriptors, dup2, pipe creation  

**What's needed:**
- Basic pipes implementation
- Redirections implementation
- Heredoc with proper delimiter parsing
- Complex combinations testing

</details>

---

### 💾 Phase 5: Environment & Variables
**Deadline:** Mar 15, 2025 | ⚠️ OVERDUE by 348 days| **Status:** 📋 PLANNED

```
Progress: ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 0%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [ ] Environment variable storage
- [ ] Variable expansion `$VAR`
- [ ] Exit status variable `$?`
- [ ] Empty variable handling
- [ ] Quote context for variables

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 14h  
**💡 Key learnings:** envp manipulation, string expansion  
**🎯 Focus:** Proper handling of variables in different quote contexts

</details>

---

### 🎯 Phase 6: Signals
**Deadline:** Mar 22, 2025 | ⚠️ OVERDUE by 341 days| **Status:** 📋 PLANNED

```
Progress: ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 0%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [ ] Handle `Ctrl+C` (SIGINT) - new prompt
- [ ] Handle `Ctrl+D` (EOF) - exit shell
- [ ] Handle `Ctrl+\` (SIGQUIT) - do nothing
- [ ] Signal handling in child processes
- [ ] Interactive vs non-interactive mode signals

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 8h  
**💡 Key learnings:** signal(), sigaction(), signal masks  

**What's needed:**
- Main process signal handling
- Child process signal inheritance
- Heredoc signal behavior

</details>

---

### 🐛 Phase 7: Testing & Bug Fixes
**Deadline:** Mar 29, 2025 | ⚠️ OVERDUE by 334 days| **Status:** 📋 PLANNED

```
Progress: ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ 0%
Timeline: ████████████████████████████████████████ [====================]
```

**Checklist:**
- [ ] Full integration testing
- [ ] Memory leak final check
- [ ] Edge case testing (empty input, special chars)
- [ ] Comparison with bash behavior
- [ ] Stress testing with complex commands
- [ ] Documentation and code cleanup

<details>
<summary>📊 <b>Details & Learnings</b></summary>

**⏱️ Time spent:** 0h  
**🎯 Focus:** Ensuring bash-like behavior in all scenarios

**Testing plan:**
- Run comprehensive test suite
- Compare outputs with bash
- Valgrind on all test cases
- Peer review

</details>

---

## 📈 Progress Visualization

### Overall Project Timeline

```
Parsing        ░░░░░░░░░░░░░░░░░░░░   0% 📋
Built-ins      ████████░░░░░░░░░░░░  43% 🚧
Execution      ░░░░░░░░░░░░░░░░░░░░   0% 📋
Pipes          ░░░░░░░░░░░░░░░░░░░░   0% 📋
Environment    ░░░░░░░░░░░░░░░░░░░░   0% 📋
Signals        ░░░░░░░░░░░░░░░░░░░░   0% 📋
Testing        ░░░░░░░░░░░░░░░░░░░░   0% 📋
```

### Time Distribution

```
Phase 1: Parsing          ███████████░░░░░░  18h
Phase 2: Built-ins        ████████░░░░░░░░░  12h
Phase 3: Execution        ██████████████░░░  22h
Phase 4: Pipes            ██████████░░░░░░░  16h
Phase 5: Environment      █████████░░░░░░░░  14h
Phase 6: Signals          ████░░░░░░░░░░░░░   8h
Phase 7: Testing          ░░░░░░░░░░░░░░░░░   0h
                                    Total: 90h
```

---

## ✨ Features & Examples

<table>
<tr>
<td width="50%">

### 🔹 Built-in Commands
```bash
minishell> echo "Hello World!"
Hello World!
minishell> cd /tmp && pwd
/tmp
minishell> export MY_VAR=42
minishell> echo $MY_VAR
42
```

</td>
<td width="50%">

### 🔹 Pipes & Redirections
```bash
minishell> ls -la | grep minishell
minishell> cat < input.txt > output.txt
minishell> echo "test" >> file.txt
minishell> cat << EOF
heredoc> Hello
heredoc> World
heredoc> EOF
```

</td>
</tr>
<tr>
<td width="50%">

### 🔹 Command Execution
```bash
minishell> /bin/ls
minishell> which gcc
/usr/bin/gcc
minishell> echo $?
0
```

</td>
<td width="50%">

### 🔹 Signal Handling
```bash
^C
minishell> 
^D
exit
```
✅ Ctrl+C (new prompt)  
✅ Ctrl+D (exit)  
✅ Ctrl+\ (ignore)  

</td>
</tr>
</table>

---

## 🏗️ Project Architecture

```
minishell/
├── src/
│   ├── main.c                 # Entry point & REPL loop
│   ├── parsing/
│   │   ├── lexer.c           # Tokenization
│   │   ├── parser.c          # Syntax tree
│   │   ├── expander.c        # Variable expansion
│   │   └── quotes.c          # Quote handling
│   ├── execution/
│   │   ├── executor.c        # Command execution
│   │   ├── pipes.c           # Pipe management
│   │   ├── redirections.c    # I/O redirections
│   │   └── heredoc.c         # Heredoc
│   ├── builtins/
│   │   ├── cd.c              # Change directory
│   │   ├── echo.c            # Echo command
│   │   ├── env.c             # Environment display
│   │   ├── exit.c            # Exit shell
│   │   ├── export.c          # Export variables
│   │   ├── pwd.c             # Print working dir
│   │   └── unset.c           # Unset variables
│   ├── signals/
│   │   └── signals.c         # Signal handling
│   └── utils/
│       ├── env_utils.c       # Environment helpers
│       ├── error.c           # Error handling
│       └── memory.c          # Memory management
├── includes/
│   └── minishell.h           # Main header
├── libft/                    # Custom C library
└── Makefile
```

---

## 🛠️ Tech Stack & Tools

<p align="center">
  <img src="https://skillicons.dev/icons?i=c,git,github,linux,bash,vim,vscode&theme=dark" />
</p>

<div align="center">

| Category | Tools |
|----------|-------|
| **Language** | C (C99 standard) |
| **Build** | Makefile, gcc/clang |
| **Libraries** | readline, libft (custom) |
| **Debugging** | GDB, Valgrind, lldb |
| **Testing** | Custom test suite, bash comparison |
| **VCS** | Git & GitHub |

</div>

---

## 🧪 Testing Strategy

### Current Test Coverage

```
Unit Tests:        ████████████████░░░░  80% (36/45 functions)
Integration Tests: ███████████░░░░░░░░░  55% (11/20 scenarios)
Memory Tests:      ███████████████████░  95% (no known leaks)
Edge Cases:        ████████░░░░░░░░░░░░  40% (needs more work)
```

### Test Commands

```bash
# Run all tests
make test

# Memory leak check
make valgrind
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Compare with bash
./test_comparison.sh

# Specific feature tests
./tests/test_pipes.sh
./tests/test_redirections.sh
./tests/test_builtins.sh
```

---

## 📚 Learning Outcomes

<table>
<tr>
<td width="50%">

### 🎓 Technical Skills
- ✅ System programming in C
- ✅ Process management (fork/exec)
- ✅ File descriptor manipulation
- ✅ Signal handling
- ✅ Memory management
- ✅ Parsing & lexical analysis

</td>
<td width="50%">

### 🔧 Tools & Practices
- ✅ Debugging with GDB
- ✅ Memory profiling (Valgrind)
- ✅ Git workflow & collaboration
- ✅ Code documentation
- ✅ Test-driven development
- ✅ 42 Norminette compliance

</td>
</tr>
</table>

---

## 🐛 Known Issues & TODO

### 🔴 Critical
- [ ] Heredoc implementation incomplete
- [ ] Signal handling in child processes needs work

### 🟡 Medium Priority
- [ ] Edge cases with multiple redirections
- [ ] Complex pipe chains (5+) need testing
- [ ] Some error messages don't match bash exactly

### 🟢 Low Priority
- [ ] Code refactoring for better modularity
- [ ] Additional test coverage
- [ ] Performance optimization

---

## 🤝 Team & Collaboration

**Developed by:**
- 👤 **Felipe & Gramos** - [@feliperamosminishell](https://github.com/feliperamosminishell)

---

## 📖 Resources & References

- 📘 [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- 🔧 [Unix System Calls](https://man7.org/linux/man-pages/)
- 💻 [42 Docs - Minishell](https://harm-smits.github.io/42docs/projects/minishell)
- 📝 [Writing a Unix Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/)

---

## 📊 Project Stats

- 📅 Started: January 15, 2025
- 🎯 Deadline: March 6, 2025  
- 💻 Language: C (C99)
- 📏 Lines of Code: ~3000+
- ✅ Norminette: Passing

---

<div align="center">

## 💬 Contact & Feedback

```bash
$ echo "Let's connect!"
```

[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/feliperamosminishell)
[![42 Intra](https://img.shields.io/badge/42_Intra-000000?style=for-the-badge&logo=42&logoColor=white)](https://profile.intra.42.fr/)


---

### ⭐ If this project helped you, consider giving it a star!

```bash
$ git add star
$ git commit -m "Thanks for the awesome work!"
$ git push origin main
```

---

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=6,11,20&height=100&section=footer" width="100%"/>

**Made with ❤️, ☕, and countless `segfaults`**

<img src="https://komarev.com/ghpvc/?username=feliperamosminishell&color=00ff41&style=flat-square&label=Profile+Views" alt="views"/>

### 📌 Last Updated: February 25, 2026 at 05:16 UTC

</div>

---

## 📝 How to Update This README

Este README se actualiza **AUTOMÁTICAMENTE** gracias a GitHub Actions.

### 🤖 Actualizaciones Automáticas

- ✅ **Barras de progreso**: Se calculan según checkboxes marcadas
- ⏱️ **Timeline**: Se actualiza según la fecha actual vs deadline
- 📊 **Estadísticas**: Tareas y tiempo se calculan automáticamente
- 🔄 **Frecuencia**: Cada día a las 00:00 UTC y con cada push

### ✏️ Solo marca las checkboxes:

```markdown
- [ ] Tarea pendiente
- [x] Tarea completada  ← Marca así cuando completes
```

El sistema actualizará todo automáticamente 🚀
