#!/usr/bin/env python3
"""
Automatic README updater for minishell project
"""

import re
from datetime import datetime
from pathlib import Path

# Configuration
DEADLINE = datetime(2026, 3, 31)
START_DATE = datetime(2026, 2, 1)

PHASE_DEADLINES = {
    1: datetime(2026, 2, 14),
    2: datetime(2026, 2, 21),
    3: datetime(2026, 3, 1),
    4: datetime(2026, 3, 8),
    5: datetime(2026, 3, 15),
    6: datetime(2026, 3, 22),
    7: datetime(2026, 3, 29),
}


def create_progress_bar(percentage, width=40):
    filled = int((percentage / 100) * width)
    return "█" * filled + "░" * (width - filled)


def calculate_phase_progress(content, phase_num):
    pattern = rf'(### .*?Phase {phase_num}:.*?\n)(.*?)(?=\n### |\Z)'
    match = re.search(pattern, content, re.DOTALL)

    if not match:
        return 0

    section = match.group(2)

    total = len(re.findall(r'- \[[ xX]\]', section))
    done = len(re.findall(r'- \[[xX]\]', section))

    if total == 0:
        return 0

    return round((done / total) * 100)


def calculate_timeline_progress(deadline):
    now = datetime.now()
    total = (deadline - START_DATE).days
    elapsed = (now - START_DATE).days

    if elapsed <= 0:
        return 0
    if elapsed >= total:
        return 100

    return round((elapsed / total) * 100)


def get_time_remaining(deadline):
    now = datetime.now()
    diff = deadline - now

    if diff.days < 0:
        return f"⚠️ OVERDUE by {abs(diff.days)} days"

    return f"📅 {diff.days}d {diff.seconds // 3600}h remaining"


def calculate_overall_progress(content):
    all_boxes = re.findall(r'- \[[ xX]\]', content)
    checked = re.findall(r'- \[[xX]\]', content)

    if not all_boxes:
        return 0, 0, 0

    percent = round(len(checked) / len(all_boxes) * 100)
    return percent, len(checked), len(all_boxes)


def calculate_total_time(content):
    times = re.findall(r'\*\*⏱️ Time spent:\*\* (\d+)h', content)
    return sum(map(int, times))


def update_phase_section(content, phase_num):
    progress = calculate_phase_progress(content, phase_num)
    timeline = calculate_timeline_progress(PHASE_DEADLINES[phase_num])
    remaining = get_time_remaining(PHASE_DEADLINES[phase_num])

    pattern = rf'(### .*?Phase {phase_num}:.*?\n)(.*?)(?=\n### |\Z)'

    def repl(match):
        header, body = match.group(1), match.group(2)

        # Progress bar
        bar = create_progress_bar(progress)
        body = re.sub(
            r'Progress:\s*[█░]+\s*\d+%',
            f'Progress: {bar} {progress}%',
            body
        )

        # Timeline bar
        tbar = create_progress_bar(timeline)
        visual = "=" * (timeline // 5) + "-" * (20 - timeline // 5)

        body = re.sub(
            r'Timeline:\s*[█░]+\s*\[.*?\]',
            f'Timeline: {tbar} [{visual}]',
            body
        )

        # Deadline
        date_str = PHASE_DEADLINES[phase_num].strftime('%b %d, %Y')
        body = re.sub(
            r'\*\*Deadline:\*\* .*?\|.*?\|',
            f'**Deadline:** {date_str} | {remaining} |',
            body
        )

        return header + body

    return re.sub(pattern, repl, content, flags=re.DOTALL)


def update_overall_section(content):
    percent, done, total = calculate_overall_progress(content)
    total_time = calculate_total_time(content)
    remaining = get_time_remaining(DEADLINE)

    # Progress bar
    bar = create_progress_bar(percent, 80)
    content = re.sub(
        r'```\n[█░]+\s+\d+%\n```',
        f'```\n{bar}  {percent}%\n```',
        content,
        count=1
    )

    # Stats
    stats_pattern = r'\*\*Completed:\*\* .*?\| \*\*Time Invested:\*\* .*?\| \*\*Deadline:\*\* .*'
    deadline_str = DEADLINE.strftime('%B %d, %Y')

    new_stats = (
        f'**Completed:** {done}/{total} tasks | '
        f'**Time Invested:** {total_time}h | '
        f'**Deadline:** {deadline_str} ({remaining})'
    )

    content = re.sub(stats_pattern, new_stats, content)

    return content


def update_progress_visualization(content):
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


def add_timestamp(content):
    now = datetime.now().strftime('%B %d, %Y at %H:%M UTC')

    if '### 📌 Last Updated:' in content:
        return re.sub(
            r'### 📌 Last Updated: .*',
            f'### 📌 Last Updated: {now}',
            content
        )

    return content


def main():
    path = Path("README.md")

    if not path.exists():
        print("README.md not found")
        return

    content = path.read_text(encoding="utf-8")

    content = update_overall_section(content)

    for i in range(1, 8):
        content = update_phase_section(content, i)

    content = update_progress_visualization(content)
    content = add_timestamp(content)

    path.write_text(content, encoding="utf-8")

    print("README updated successfully")


if __name__ == "__main__":
    main()
