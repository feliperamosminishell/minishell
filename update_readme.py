#!/usr/bin/env python3
"""
Automatic README updater for minishell project
Updates progress bars and timelines based on checkbox completion and current date
"""

import re
from datetime import datetime, timedelta
from pathlib import Path

# Configuration
DEADLINE = datetime(2025, 3, 6)  # 6 de marzo de 2025
START_DATE = datetime(2025, 1, 15)  # Fecha de inicio del proyecto

PHASE_DEADLINES = {
    1: datetime(2025, 2, 14),
    2: datetime(2025, 2, 21),
    3: datetime(2025, 3, 1),
    4: datetime(2025, 3, 8),
    5: datetime(2025, 3, 15),
    6: datetime(2025, 3, 22),
    7: datetime(2025, 3, 29),
}


def create_progress_bar(percentage, width=40, filled='█', empty='░'):
    """Create ASCII progress bar"""
    filled_blocks = int((percentage / 100) * width)
    empty_blocks = width - filled_blocks
    return filled * filled_blocks + empty * empty_blocks


def calculate_phase_progress(readme_content, phase_num):
    """Calculate progress for a specific phase based on checked checkboxes"""
    # Find the phase section
    phase_pattern = rf'### .*?Phase {phase_num}:.*?\n(.*?)(?=###|\Z)'
    phase_match = re.search(phase_pattern, readme_content, re.DOTALL)
    
    if not phase_match:
        return 0
    
    phase_content = phase_match.group(1)
    
    # Count checkboxes
    total_boxes = len(re.findall(r'- \[[ x]\]', phase_content))
    checked_boxes = len(re.findall(r'- \[x\]', phase_content))
    
    if total_boxes == 0:
        return 0
    
    return round((checked_boxes / total_boxes) * 100)


def calculate_timeline_progress(phase_deadline):
    """Calculate timeline progress from start to deadline"""
    now = datetime.now()
    total_duration = (phase_deadline - START_DATE).days
    elapsed = (now - START_DATE).days
    
    if elapsed < 0:
        return 0
    if elapsed >= total_duration:
        return 100
    
    return round((elapsed / total_duration) * 100)


def get_time_remaining(deadline):
    """Calculate time remaining until deadline"""
    now = datetime.now()
    remaining = deadline - now
    
    if remaining.days < 0:
        days_over = abs(remaining.days)
        return f"⚠️ OVERDUE by {days_over} days", True
    
    days = remaining.days
    hours = remaining.seconds // 3600
    
    if days == 0:
        return f"⏰ {hours}h remaining", False
    return f"📅 {days}d {hours}h remaining", False


def calculate_overall_progress(readme_content):
    """Calculate overall project progress"""
    all_boxes = re.findall(r'- \[[ x]\]', readme_content)
    checked_boxes = [box for box in all_boxes if '[x]' in box]
    
    if len(all_boxes) == 0:
        return 0, 0, len(all_boxes)
    
    percentage = round((len(checked_boxes) / len(all_boxes)) * 100)
    return percentage, len(checked_boxes), len(all_boxes)


def calculate_total_time(readme_content):
    """Calculate total time invested from all phases"""
    time_pattern = r'\*\*⏱️ Time spent:\*\* (\d+)h'
    times = re.findall(time_pattern, readme_content)
    return sum(int(t) for t in times)


def update_phase_section(readme_content, phase_num):
    """Update a single phase section with current progress and timeline"""
    progress = calculate_phase_progress(readme_content, phase_num)
    timeline_progress = calculate_timeline_progress(PHASE_DEADLINES[phase_num])
    time_remaining, is_overdue = get_time_remaining(PHASE_DEADLINES[phase_num])
    
    # Find phase section
    phase_pattern = rf'(### .*?Phase {phase_num}:.*?\n)(.*?)(?=###|\Z)'
    
    def replacer(match):
        header = match.group(1)
        content = match.group(2)
        
        # Update progress bar
        progress_bar = create_progress_bar(progress)
        content = re.sub(
            r'Progress: [█░]+ \d+%',
            f'Progress: {progress_bar} {progress}%',
            content
        )
        
        # Update timeline bar
        timeline_bar = create_progress_bar(timeline_progress)
        timeline_visual = '=' * (timeline_progress // 5) + '-' * (20 - timeline_progress // 5)
        content = re.sub(
            r'Timeline: [█░]+ \[.*?\]',
            f'Timeline: {timeline_bar} [{timeline_visual}]',
            content
        )
        
        # Update deadline info (if it exists)
        deadline_date = PHASE_DEADLINES[phase_num].strftime('%b %d, %Y')
        content = re.sub(
            r'\*\*Deadline:\*\* [^|]+\|[^|]+',
            f'**Deadline:** {deadline_date} | {time_remaining}',
            content
        )
        
        return header + content
    
    return re.sub(phase_pattern, replacer, readme_content, flags=re.DOTALL)


def update_overall_section(readme_content):
    """Update overall progress section"""
    percentage, completed, total = calculate_overall_progress(readme_content)
    total_time = calculate_total_time(readme_content)
    overall_time_remaining, is_overdue = get_time_remaining(DEADLINE)
    
    # Update overall progress bar
    progress_bar = create_progress_bar(percentage, width=80)
    readme_content = re.sub(
        r'```\n[█░]+\s+\d+%\n```',
        f'```\n{progress_bar}  {percentage}%\n```',
        readme_content,
        count=1
    )
    
    # Update stats
    stats_pattern = r'\*\*Completed:\*\* \d+/\d+ tasks \| \*\*Time Invested:\*\* \d+h \| \*\*Deadline:\*\* .*?\)'
    deadline_str = DEADLINE.strftime('%B %d, %Y')
    new_stats = f'**Completed:** {completed}/{total} tasks | **Time Invested:** {total_time}h | **Deadline:** {deadline_str} ({overall_time_remaining})'
    readme_content = re.sub(stats_pattern, new_stats, readme_content)
    
    return readme_content


def update_progress_visualization(readme_content):
    """Update the overall progress visualization section"""
    phases = {
        'Parsing': calculate_phase_progress(readme_content, 1),
        'Built-ins': calculate_phase_progress(readme_content, 2),
        'Execution': calculate_phase_progress(readme_content, 3),
        'Pipes': calculate_phase_progress(readme_content, 4),
        'Environment': calculate_phase_progress(readme_content, 5),
        'Signals': calculate_phase_progress(readme_content, 6),
        'Testing': calculate_phase_progress(readme_content, 7),
    }
    
    # Update each phase visualization
    for phase_name, percentage in phases.items():
        bar = create_progress_bar(percentage, width=20)
        
        # Determine status emoji
        if percentage == 100:
            status = '✅'
        elif percentage > 0:
            status = '🚧'
        else:
            status = '📋'
        
        pattern = rf'{phase_name}\s+[█░]+\s+\d+%\s+[✅🚧📋]'
        replacement = f'{phase_name:<15}{bar} {percentage:>3}% {status}'
        readme_content = re.sub(pattern, replacement, readme_content)
    
    return readme_content


def add_last_updated_timestamp(readme_content):
    """Add or update last updated timestamp"""
    now = datetime.now().strftime('%B %d, %Y at %H:%M UTC')
    
    # Look for existing timestamp
    if '### 📌 Last Updated:' in readme_content:
        readme_content = re.sub(
            r'### 📌 Last Updated: .*',
            f'### 📌 Last Updated: {now}',
            readme_content
        )
    else:
        # Add before closing div
        readme_content = readme_content.replace(
            '</div>\n\n---\n\n## 📝 How to Update This README',
            f'### 📌 Last Updated: {now}\n\n</div>\n\n---\n\n## 📝 How to Update This README'
        )
    
    return readme_content


def main():
    """Main function to update README"""
    readme_path = Path('README.md')
    
    if not readme_path.exists():
        print("❌ README.md not found!")
        return
    
    print("📖 Reading README.md...")
    readme_content = readme_path.read_text(encoding='utf-8')
    
    print("🔄 Updating overall progress...")
    readme_content = update_overall_section(readme_content)
    
    print("🔄 Updating phase sections...")
    for phase_num in range(1, 8):
        print(f"   └─ Phase {phase_num}...")
        readme_content = update_phase_section(readme_content, phase_num)
    
    print("🔄 Updating progress visualization...")
    readme_content = update_progress_visualization(readme_content)
    
    print("🔄 Adding timestamp...")
    readme_content = add_last_updated_timestamp(readme_content)
    
    print("💾 Writing updated README.md...")
    readme_path.write_text(readme_content, encoding='utf-8')
    
    print("✅ README.md updated successfully!")
    
    # Print summary
    percentage, completed, total = calculate_overall_progress(readme_content)
    print(f"\n📊 Summary:")
    print(f"   Progress: {percentage}% ({completed}/{total} tasks)")
    print(f"   Total time: {calculate_total_time(readme_content)}h")
    time_remaining, is_overdue = get_time_remaining(DEADLINE)
    print(f"   Deadline: {time_remaining}")


if __name__ == '__main__':
    main()
