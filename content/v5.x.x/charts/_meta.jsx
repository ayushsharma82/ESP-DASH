import Badge from "@/components/Badge";
import NewBadge from "@/components/NewBadge";

const metadata = {
  "bar": {
    title: "Bar"
  },
  "line": {
    title: <span className="flex items-center justify-center gap-2">Line <Badge /></span>
  },
  "area": {
    title: <span className="flex items-center justify-center gap-2">Area <Badge /></span>
  },
  "pie": {
    title: <span className="flex items-center justify-center gap-2">Pie <Badge /></span>
  },
  "doughnut": {
    title: <span className="flex items-center justify-center gap-2">Doughnut <NewBadge /> <Badge /></span>
  }
}

export default metadata