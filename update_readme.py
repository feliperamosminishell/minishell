#!/usr/bin/env python3
import re
from datetime import datetime
from pathlib import Path

# ================= CONFIG ================= #

CURRENT_YEAR = datetime.now().year

DEADLINE = datetime(CURRENT_YEAR, 3, 30)
START_DATE = datetime(CURRENT_YEAR, 1, 31)

PHASE_DEADLINES = {
    1: datetime(CURRENT_YEAR, 2, 14),
    2: datetime(CURRENT_YEAR, 2, 21),
    3: datetime(CURRENT_YEAR, 3, 1),
    4: datetime(CURRENT_YEAR, 3, 8),
    5: datetime(CURRENT_YEAR, 3, 15),
    6: datetime(CURRENT_YEAR, 3, 22),
    7: datetime(CURRENT_YEAR, 3, 29),
}

# ================= UTILS ================= #

def create_progress_bar(p, width=40):
    filled = int((p / 100) * width)
    return "█" * filled + "░" * (width - filled)


def get_status(p):
    if p == 100:
        return "✅ COMPLETED"
    elif p > 0:
        return "🚧 IN PROGRESS"
    return "📋 PLANNED"


def get_time_remaining(deadline):
    now = datetime.now()
    diff = deadline - now

    if diff.days < 0:
        return f"⚠️ OVERDUE by {abs(diff.days)} days"

    return f"📅 {diff.days}d {diff.seconds // 3600}h remaining"


# ================= CALCULATIONS ================= #

def calculate_phase_progress(content, phase):
    pattern = rf'(### .*?Phase {phase}:.*?\n)(.*?)(?=\n### |\Z)'
    match = re.search(pattern, content, re.DOTALL)

    if not match:
        return 0

    section = match.group(2)

    total = len(re.findall(r'- \[[ xX]\]', section))
    done = len(re.findall(r'- \[[xX]\]', section))

    return round((done / total) * 100) if total else 0


def calculate_overall(content):
    all_boxes = re.findall(r'- \[[ xX]\]', content)
    checked = re.findall(r'- \[[xX]\]', content)

    if not all_boxes:
        return 0, 0, 0

    return round(len(checked)/len(all_boxes)*100), len(checked), len(all_boxes)


def calculate_total_time(content):
    times = re.findall(r'\*\*⏱️ Time spent:\*\* (\d+)h', content)
    return sum(map(int, times))


# ================= UPDATE SECTIONS ================= #

def update_phase(content, phase):
    progress = calculate_phase_progress(content, phase)
    timeline = calculate_timeline(PHASE_DEADLINES[phase])
    status = get_status(progress)

    pattern = rf'(### .*?Phase {phase}:.*?\n)(.*?)(?=\n### |\Z)'

    def repl(m):
        header, body = m.group(1), m.group(2)

        # Progress
        bar = create_progress_bar(progress)
        body = re.sub(r'Progress:\s*[█░]+\s*\d+%', f'Progress: {bar} {progress}%', body)

        # Timeline
        tbar = create_progress_bar(timeline)
        visual = "=" * (timeline // 5) + "-" * (20 - timeline // 5)

        body = re.sub(
            r'Timeline:\s*[█░]+\s*\[.*?\]',
            f'Timeline: {tbar} [{visual}]',
            body
        )

        # Deadline + Status (FIX TOTAL)
        date_str = PHASE_DEADLINES[phase].strftime('%b %d, %Y')

        if status == "✅ COMPLETED":
            line = f'**Deadline:** {date_str} | **Status:** {status}'
        else:
            remaining = get_time_remaining(PHASE_DEADLINES[phase])
            line = f'**Deadline:** {date_str} | {remaining} | **Status:** {status}'

        body = re.sub(r'\*\*Deadline:\*\*.*', line, body)

        return header + body

    return re.sub(pattern, repl, content, flags=re.DOTALL)


def calculate_timeline(deadline):
    now = datetime.now()
    total = (deadline - START_DATE).days
    elapsed = (now - START_DATE).days

    if elapsed <= 0:
        return 0
    if elapsed >= total:
        return 100

    return round((elapsed / total) * 100)


def update_overall(content):
    percent, done, total = calculate_overall(content)
    time = calculate_total_time(content)

    bar = create_progress_bar(percent, 80)

    content = re.sub(
        r'```\n[█░]+\s+\d+%\n```',
        f'```\n{bar}  {percent}%\n```',
        content,
        count=1
    )

    stats = (
        f'**Completed:** {done}/{total} tasks | '
        f'**Time Invested:** {time}h | '
        f'**Deadline:** {DEADLINE.strftime("%B %d, %Y")}'
    )

    content = re.sub(
        r'\*\*Completed:\*\* .*?\| \*\*Time Invested:\*\* .*?\| \*\*Deadline:\*\* .*',
        stats,
        content
    )

    return content


def update_time_progress(content):
    now = datetime.now()

    total = (DEADLINE - START_DATE).days
    elapsed = (now - START_DATE).days

    if elapsed <= 0:
        percent = 0
    elif elapsed >= total:
        percent = 100
    else:
        percent = round((elapsed / total) * 100)

    bar = create_progress_bar(percent)
    visual = "=" * (percent // 5) + "-" * (20 - percent // 5)

    return re.sub(
        r'(### ⏱️ Time Progress\n```)[\s\S]*?```',
        f'\\1\n{bar}  {percent}%  [{visual}]\n```',
        content
    )


def update_visual(content):
    phases = {
        'Parsing': 1,
        'Built-ins': 2,
        'Execution': 3,
        'Pipes': 4,
        'Environment': 5,
        'Signals': 6,
        'Testing': 7,
    }

    for name, num in phases.items():
        p = calculate_phase_progress(content, num)
        bar = create_progress_bar(p, 20)
        status = '✅' if p == 100 else '🚧' if p > 0 else '📋'

        content = re.sub(
            rf'{name}\s+[█░]+\s+\d+%\s+[✅🚧📋]',
            f'{name:<15}{bar} {p:>3}% {status}',
            content
        )

    return content


def update_timestamp(content):
    now = datetime.now().strftime('%B %d, %Y at %H:%M UTC')

    return re.sub(
        r'### 📌 Last Updated: .*',
        f'### 📌 Last Updated: {now}',
        content
    )


# ================= MAIN ================= #

def main():
    path = Path("README.md")

    if not path.exists():
        print("README.md not found")
        return

    content = path.read_text(encoding="utf-8")

    content = update_overall(content)
    content = update_time_progress(content)

    for i in range(1, 8):
        content = update_phase(content, i)

    content = update_visual(content)
    content = update_timestamp(content)

    path.write_text(content, encoding="utf-8")

    print("✅ README updated perfectly")


if __name__ == "__main__":
    main()
