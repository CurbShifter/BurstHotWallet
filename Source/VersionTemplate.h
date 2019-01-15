// SubWCRev
#ifndef __PROJECT_SubWCRev__
#define __PROJECT_SubWCRev__

#define PROJECT_SVNRevisionN $WCREV$
#define PROJECT_SVNRevision "$WCREV$"
#define PROJECT_SVNModified "$WCMODS?Modified:Not modified$"
#define PROJECT_SVNDate     "$WCDATE$"
#define PROJECT_SVNRange    "WCRANGE$"
#define PROJECT_SVNMixed    "$WCMIXED?Mixed revision:Not mixed$"
#define PROJECT_SVNURL      "$WCURL$"

//#if $WCMODS?1:0$
//	#error Source is modified
//#endif

#endif //PROJECT_SubWCRev
