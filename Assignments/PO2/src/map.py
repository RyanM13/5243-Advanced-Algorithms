import json
import os
import matplotlib.pyplot as plt
import numpy as np

structures = ["bst", "ht", "ll", "sa"]
struct_labels = ["BST", "Hash Table", "Linked List", "Sorted Array"]
workloads = ["A", "B", "C", "D"]
sizes = [1000, 5000, 10000, 20000]
counters = [
    "comparisons",
    "structural_ops",
    "inserts",
    "deletes",
    "lookups",
    "resize_events",
]
counter_labels = {
    "comparisons": "Comparisons",
    "structural_ops": "Structural Ops",
    "inserts": "Inserts",
    "deletes": "Deletes",
    "lookups": "Lookups",
    "resize_events": "Resize Events",
}


def load_results():
    data = {}
    for struct in structures:
        data[struct] = {}
        for w in workloads:
            data[struct][w] = {}
            for n in sizes:
                filename = f"results/{struct}_{w}_{n}.json"
                if os.path.exists(filename):
                    with open(filename) as f:
                        data[struct][w][n] = json.load(f)
                else:
                    print(f"Warning: missing file {filename}")
                    data[struct][w][n] = {c: 0 for c in counters}
    return data


def make_heatmaps(data):
    os.makedirs("charts/heatmap", exist_ok=True)

    col_labels = [f"{w}-{n}" for w in workloads for n in sizes]

    for counter in counters:
        matrix = []
        for struct in structures:
            row = []
            for w in workloads:
                for n in sizes:
                    val = data[struct][w][n].get(counter, 0)
                    row.append(val)
            matrix.append(row)

        matrix = np.array(matrix)

        fig, ax = plt.subplots(figsize=(18, 5))
        im = ax.imshow(matrix, cmap="YlOrRd", aspect="auto")

        # labels
        ax.set_xticks(range(len(col_labels)))
        ax.set_xticklabels(col_labels, rotation=45, ha="right", fontsize=9)
        ax.set_yticks(range(len(struct_labels)))
        ax.set_yticklabels(struct_labels, fontsize=11)

        for i in range(len(structures)):
            for j in range(len(col_labels)):
                val = matrix[i][j]
                ax.text(
                    j,
                    i,
                    f"{val:,}",
                    ha="center",
                    va="center",
                    fontsize=7,
                    color="black" if val < matrix.max() * 0.7 else "white",
                )

        plt.colorbar(im, ax=ax)
        ax.set_title(
            f"{counter_labels[counter]} — All Structures vs All Workloads", fontsize=14
        )
        plt.tight_layout()

        filename = f"charts/heatmap/{counter}_heatmap.png"
        plt.savefig(filename)
        plt.close()
        print(f"Saved: {filename}")


if __name__ == "__main__":
    data = load_results()
    make_heatmaps(data)
